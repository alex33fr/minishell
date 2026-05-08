#!/bin/bash

# Lance toute la suite de tests avec valgrind
# Usage: bash run_all.sh
# Logs : logs_full_test.txt (écrasé à chaque run)

cd "$(dirname "$0")"

LOGFILE="./logs_full_test.txt"
> "$LOGFILE"

# Crée readline.supp si absent
if [ ! -f ./readline.supp ]; then
	cat > ./readline.supp <<'SUPP'
{
   readline_leaks
   Memcheck:Leak
   ...
   fun:readline
}
{
   readline_leaks_2
   Memcheck:Leak
   ...
   fun:rl_*
}
{
   add_history_leaks
   Memcheck:Leak
   ...
   fun:add_history
}
{
   history_leaks
   Memcheck:Leak
   ...
   fun:history_*
}
{
   readline_internal
   Memcheck:Leak
   ...
   obj:*/libreadline.so*
}
{
   ncurses_leaks
   Memcheck:Leak
   ...
   obj:*/libncurses.so*
}
{
   ncurses_tinfo_leaks
   Memcheck:Leak
   ...
   obj:*/libtinfo.so*
}
SUPP
	echo "[INFO] readline.supp créé automatiquement"
fi

MINI="./minishell"
VG="valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
    --track-origins=yes --suppressions=./readline.supp \
    --error-exitcode=99 -q"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
BOLD='\033[1m'
NC='\033[0m'

TOTAL_PASS=0
TOTAL_WARN=0
TOTAL_FAIL=0
TOTAL_LEAK=0
TOTAL_CRASH=0
TEST_NUM=0
CURRENT_SECTION=""

normalize() {
	sed 's/^bash: line [0-9]*: //' | sed 's/^minishell: //'
}

# Écriture dans le log (texte propre, sans codes ANSI)
log() { printf '%s\n' "$*" >> "$LOGFILE"; }

log_header() {
	log ""
	log "════════════════════════════════════════════════════"
	log "  $1"
	log "════════════════════════════════════════════════════"
}

log_test() {
	local num="$1" desc="$2" status="$3" input="$4"
	local mini_o="$5" mini_e="$6" mini_x="$7"
	local bash_o="$8" bash_e="$9" bash_x="${10}"
	local leak_info="${11}"

	log ""
	log "Test ${num}: ${desc}  [${status}]"
	log "\$> $(echo "$input" | head -1)"
	if [ "$status" = "OK" ] || [ "$status" = "OK+LEAK" ]; then
		[ -n "$mini_o" ] && log "  sortie : $(echo "$mini_o" | head -3 | tr '\n' '|' | sed 's/|$//')"
	else
		log "  minishell [exit=${mini_x}]:"
		[ -n "$mini_o" ] && log "    stdout : $(echo "$mini_o" | head -3 | tr '\n' '↵ ' | sed 's/ $//')"
		[ -n "$mini_e" ] && log "    stderr : $(echo "$mini_e" | head -3 | tr '\n' '↵ ' | sed 's/ $//')"
		log "  bash      [exit=${bash_x}]:"
		[ -n "$bash_o" ] && log "    stdout : $(echo "$bash_o" | head -3 | tr '\n' '↵ ' | sed 's/ $//')"
		[ -n "$bash_e" ] && log "    stderr : $(echo "$bash_e" | head -3 | tr '\n' '↵ ' | sed 's/ $//')"
		if [ "$mini_x" != "$bash_x" ]; then
			log "  !! exit code différent : minishell=${mini_x}  bash=${bash_x}"
		fi
		if [ "$mini_o" != "$bash_o" ]; then
			log "  !! stdout différent"
		fi
		if [ "$mini_e" != "$bash_e" ]; then
			log "  !! stderr différent"
		fi
	fi
	if [ -n "$leak_info" ]; then
		log "  --- VALGRIND OUTPUT COMPLET ---"
		while IFS= read -r line; do
			log "    $line"
		done <<< "$leak_info"
		log "  --- FIN VALGRIND ---"
	fi
}

# ─────────────────────────────────────────────
# Comparaison bash vs mini + valgrind
check() {
	local desc="$1"
	local input="$2"
	((TEST_NUM++))

	mini_out=$(printf '%s' "$input" | timeout 5 "$MINI" 2>/tmp/ra_mini_err_$$)
	mini_exit=$?
	mini_err=$(cat /tmp/ra_mini_err_$$ | normalize)

	bash_out=$(printf '%s' "$input" | timeout 5 bash --norc --noprofile 2>/tmp/ra_bash_err_$$)
	bash_exit=$?
	bash_err=$(cat /tmp/ra_bash_err_$$ | normalize)

	rm -f /tmp/ra_mini_err_$$ /tmp/ra_bash_err_$$

	vg_out=$(printf '%s' "$input" | timeout 10 $VG "$MINI" 2>/tmp/ra_vg_$$)
	vg_code=$?
	vg_full=$(cat /tmp/ra_vg_$$)
	vg_leak=$(grep -E "definitely lost|indirectly lost|still reachable" /tmp/ra_vg_$$ | grep -v "0 bytes")
	vg_err2=$(grep "ERROR SUMMARY" /tmp/ra_vg_$$ | grep -v "0 errors")
	rm -f /tmp/ra_vg_$$

	local fail=0
	local warn=0
	local leak=0

	[ "$mini_exit" != "$bash_exit" ] && fail=1
	[ "$mini_out"  != "$bash_out"  ] && fail=1
	[ "$mini_err"  != "$bash_err"  ] && warn=1

	if [ $vg_code -eq 99 ] || [ -n "$vg_leak" ] || [ -n "$vg_err2" ]; then
		leak=1
		((TOTAL_LEAK++))
	fi

	local status
	if [ $fail -eq 1 ]; then
		status="FAIL"
		echo -e "${RED}[FAIL]${NC} ${desc}"
		((TOTAL_FAIL++))
	elif [ $warn -eq 1 ]; then
		status="WARN"
		echo -e "${YELLOW}[WARN]${NC} ${desc}"
		((TOTAL_WARN++))
	else
		status="OK"
		echo -e "${GREEN}[OK  ]${NC} ${desc}"
		((TOTAL_PASS++))
	fi
	[ $leak -eq 1 ] && status="${status}+LEAK"

	echo -e "  ${CYAN}\$>${NC} $(echo "$input" | head -1)"
	echo -e "  ${GREEN}my minishell${NC} [exit=${mini_exit}]: $(echo "${mini_out}${mini_err}" | head -3 | tr '\n' ' ')"
	echo -e "  ${YELLOW}original bash${NC} [exit=${bash_exit}]: $(echo "${bash_out}${bash_err}" | head -3 | tr '\n' ' ')"
	if [ $fail -eq 1 ]; then
		[ "$mini_exit" != "$bash_exit" ] && echo -e "  ${RED}!! exit différent${NC}"
		[ "$mini_out"  != "$bash_out"  ] && echo -e "  ${RED}!! stdout différent${NC}"
		[ "$mini_err"  != "$bash_err"  ] && echo -e "  ${RED}!! stderr différent${NC}"
	elif [ $warn -eq 1 ]; then
		echo -e "  ${YELLOW}!! stderr différent${NC}"
	fi
	if [ $leak -eq 1 ]; then
		echo -e "  ${RED}leaks valgrind:${NC}"
		echo "$vg_full" | grep -v "^$" | sed 's/^/    /'
	fi
	log_test "$TEST_NUM" "$desc" "$status" "$input" \
		"$mini_out" "$mini_err" "$mini_exit" \
		"$bash_out" "$bash_err" "$bash_exit" "$vg_full"
}

# Crash only + valgrind (pas de comparaison bash)
vcheck() {
	local desc="$1"
	local input="$2"
	local env_prefix="${3:-}"
	((TEST_NUM++))

	if [ -n "$env_prefix" ]; then
		mini_out=$(printf '%s' "$input" | timeout 5 env -i $env_prefix "$MINI" 2>/tmp/ra_mini_err_$$)
	else
		mini_out=$(printf '%s' "$input" | timeout 5 "$MINI" 2>/tmp/ra_mini_err_$$)
	fi
	mini_exit=$?
	rm -f /tmp/ra_mini_err_$$

	if [ $mini_exit -eq 124 ]; then
		echo -e "${RED}[TIMEOUT]${NC} ${desc}"
		echo -e "  ${CYAN}\$>${NC} $(echo "$input" | head -1)"
		((TOTAL_CRASH++))
		log ""; log "Test ${TEST_NUM}: ${desc}  [TIMEOUT]"
		log "\$> $(echo "$input" | head -1)"
		return
	fi
	if [ $mini_exit -ge 134 ] && [ $mini_exit -le 139 ]; then
		echo -e "${RED}[CRASH  ]${NC} ${desc} (exit=$mini_exit)"
		echo -e "  ${CYAN}\$>${NC} $(echo "$input" | head -1)"
		((TOTAL_CRASH++))
		log ""; log "Test ${TEST_NUM}: ${desc}  [CRASH exit=${mini_exit}]"
		log "\$> $(echo "$input" | head -1)"
		return
	fi

	if [ -n "$env_prefix" ]; then
		vg_out=$(printf '%s' "$input" | timeout 10 env -i $env_prefix $VG "$MINI" 2>/tmp/ra_vg_$$)
	else
		vg_out=$(printf '%s' "$input" | timeout 10 $VG "$MINI" 2>/tmp/ra_vg_$$)
	fi
	vg_code=$?
	vg_full=$(cat /tmp/ra_vg_$$)
	vg_leak=$(grep -E "definitely lost|indirectly lost|still reachable" /tmp/ra_vg_$$ | grep -v "0 bytes")
	vg_errs=$(grep "ERROR SUMMARY" /tmp/ra_vg_$$ | grep -v "0 errors")
	rm -f /tmp/ra_vg_$$

	if [ $vg_code -eq 99 ] || [ -n "$vg_leak" ] || [ -n "$vg_errs" ]; then
		echo -e "${RED}[LEAK  ]${NC} ${desc}"
		echo -e "  ${CYAN}\$>${NC} $(echo "$input" | head -1)"
		echo -e "  ${GREEN}my minishell${NC} [exit=${mini_exit}]: $(echo "${mini_out}" | head -3 | tr '\n' ' ')"
		echo -e "  ${RED}leaks valgrind:${NC}"
		echo "$vg_full" | grep -v "^$" | sed 's/^/    /'
		((TOTAL_LEAK++))
		((TOTAL_PASS++))
		log ""; log "Test ${TEST_NUM}: ${desc}  [LEAK]"
		log "\$> $(echo "$input" | head -1)"
		log "  --- VALGRIND OUTPUT COMPLET ---"
		while IFS= read -r line; do
			log "    $line"
		done <<< "$vg_full"
		log "  --- FIN VALGRIND ---"
	else
		echo -e "${GREEN}[CLEAN ]${NC} ${desc}"
		echo -e "  ${CYAN}\$>${NC} $(echo "$input" | head -1)"
		echo -e "  ${GREEN}my minishell${NC} [exit=${mini_exit}]: $(echo "${mini_out}" | head -3 | tr '\n' ' ')"
		((TOTAL_PASS++))
		log ""; log "Test ${TEST_NUM}: ${desc}  [OK]"
		log "\$> $(echo "$input" | head -1)"
	fi
}

section() {
	echo -e "\n${BOLD}${CYAN}$1${NC}"
	CURRENT_SECTION="$1"
	log_header "$1"
}

# Snapshot des fichiers présents avant les tests
_BEFORE_FILES=$(ls -1 . 2>/dev/null | sort)

# ─────────────────────────────────────────────
echo -e "${CYAN}================================================================${NC}"
echo -e "${CYAN}  MINISHELL — ALL TESTS + VALGRIND${NC}"
echo -e "${CYAN}================================================================${NC}"

# ══════════════════════════════════════════════
section "[1] PIPES"
# ══════════════════════════════════════════════
check  "simple pipe"                  "echo hello | cat"
check  "triple pipe"                  "echo a | cat | cat"
check  "pipe chain 6"                 "ls | cat | cat | cat | cat | cat"
check  "pipe invalid cmds"            "ls | ldkdkd | ls | lk"
check  "pipe no left"                 "| ls"
check  "pipe no right"                "ls |"
check  "pipe empty string"            "echo '' | cat"
check  "pipe newline"                 'printf "a\nb\nc" | wc -l'
check  "pipe to grep"                 "echo hello | grep hello"
check  "pipe many invalid"            "lkjh | lkjh | lkjh | lkjh | lkjh"
check  "pipe exit code"               "false | true"
check  "pipe all invalid 10x"         "$(python3 -c "print(' | '.join(['invalid_xyz']*10))")"
vcheck "pipe 20x ls"                  "$(python3 -c "print(' | '.join(['ls']*20))")"
vcheck "pipe 50x ls"                  "$(python3 -c "print(' | '.join(['ls']*50))")"

# ══════════════════════════════════════════════
section "[2] REDIRECTIONS"
# ══════════════════════════════════════════════
vcheck "redirect out"                 "echo hello > /tmp/ra_out.txt"
vcheck "redirect append"              "echo hello >> /tmp/ra_app.txt"
vcheck "redirect in"                  "cat < /tmp/ra_out.txt"
check  "redirect no file >"           "> "
check  "redirect no file <"           "< "
check  "redirect no file >>"          ">> "
check  "redirect no file <<"          "cat <<"
check  "redirect nonexist <"          "cat < /nonexistent_file_xyz"
check  "> dossier"                    "echo hi > /tmp"
check  "< dossier"                    "cat < /tmp"
check  "> sans permission"            "echo hi > /root/noperm_xyz.txt"
check  ">> sans permission"           "echo hi >> /root/noperm_xyz.txt"
vcheck "multiple > same cmd"          "echo hi > /tmp/ra_m1.txt > /tmp/ra_m2.txt"
check  "> /dev/full"                  "echo hi > /dev/full"
vcheck "pipe then redir"              "echo hi | cat > /tmp/ra_pr.txt"

# ──── >>> / <<< et séquences longues ────
check  ">>> triple out"               "echo hi >>> /tmp/ra_trip.txt"
check  "<<< here-string"              "cat <<< hello"
check  "<<<< quadruple"               "cat <<<< hello"
check  ">>>> quadruple out"           "echo hi >>>> /tmp/ra_quad.txt"
check  ">>>>>>>>>> 10x out"           "echo hi >>>>>>>>>> /tmp/ra_10.txt"
check  "<<<<<<<<<< 10x in"            "cat <<<<<<<<<< hello"
check  ">>>>>>>>>>>>>>>> 16x out"     "echo hi >>>>>>>>>>>>>>>> /tmp/ra_16.txt"
check  "<<<<<<<<<<<<<<<< 16x in"      "cat <<<<<<<<<<<<<<<< hello"
check  ">>> sans fichier"             ">>>"
check  "<<< sans arg"                 "<<<"
check  ">>>> sans fichier"            ">>>>"
check  "<<<< sans arg"                "<<<<<"

# ──── combinaisons >>> avec pipes ────
check  "pipe puis >>>"                "echo hi | cat >>> /tmp/ra_ptrip.txt"
check  ">>> puis pipe"                "echo hi >>> /tmp/ra_trip2.txt | cat"
check  "ls | >>> /tmp"                "ls | >>> /tmp/ra_pleft.txt"
check  ">>> | cat"                    ">>> /tmp/ra_pr3.txt | cat"
check  "pipe | <<< | pipe"            "echo x | cat <<< hello | cat"
check  "multi >>> dans cmd"           "echo hi >>> /tmp/a.txt >>> /tmp/b.txt"
check  ">>> nonexist dir"             "echo hi >>> /nonexist_dir_xyz/file.txt"
check  "<<< avec pipe gauche"         "echo hi | cat <<< world"
check  "<<< avec pipe droit"          "cat <<< hello | cat"
check  "<<< puis >>> dans pipe"       "cat <<< hello | cat >>> /tmp/ra_combo.txt"
check  "pipe | <<< vide"              "echo x | cat <<<"
check  "pipe | >>> vide"              "echo x | >>>"
check  "<<< puis < combiné"           "cat <<< hello < /tmp/ra_out.txt"
check  ">>> puis > combiné"           "echo hi >>> /tmp/a.txt > /tmp/b.txt"
check  "<<< dans pipe long"           "cat <<< hi | cat | cat | cat | cat"
check  ">>> dans pipe long"           "echo hi | cat | cat >>> /tmp/ra_long.txt | cat"
check  "< < < espace séparé"          "cat < < < hello"
check  "> > > espace séparé"          "echo hi > > > /tmp/ra_sp.txt"

# ══════════════════════════════════════════════
section "[3] HEREDOC"
# ══════════════════════════════════════════════
vcheck "heredoc basic"                $'cat <<EOF\nhello world\nEOF'
vcheck "heredoc empty"                $'cat <<EOF\nEOF'
vcheck "heredoc no term"              "cat <<EOF"
vcheck "heredoc with var"             $'cat <<EOF\n$HOME\nEOF'
vcheck "heredoc quoted delim"         $'cat <<"EOF"\n$HOME\nEOF'
vcheck "heredoc pipe after"           $'cat <<EOF | cat\nhello\nEOF'

# ══════════════════════════════════════════════
section "[4] QUOTES"
# ══════════════════════════════════════════════
check  "double quotes basic"          'echo "hello world"'
check  "single quotes basic"          "echo 'hello world'"
check  "mixed quotes"                 "echo \"hello\" 'world'"
check  "unclosed double"              'echo "hello'
check  "unclosed single"              "echo 'hello"
check  "empty double quotes"          'echo ""'
check  "empty single quotes"          "echo ''"
check  "quote avec dollar"            'echo "$HOME"'
check  "single no expand"             "echo '\$HOME'"
check  "nested single in double"      'echo "hel'"'"'lo"'
check  "double in single"             "echo 'hel\"lo'"
check  "quote with pipe"              'echo "a|b"'
check  "quote with redirect"          'echo "a>b"'
check  "alternating quotes"           "echo 'a'\"b\"'c'\"d\""

# ══════════════════════════════════════════════
section "[5] VARIABLES / EXPANSION"
# ══════════════════════════════════════════════
check  "expand HOME"                  "echo \$HOME"
check  "expand PATH"                  "echo \$PATH"
check  "expand var inexistante"       "echo \$NONEXISTENT_VAR_XYZ"
check  "expand ?"                     "echo \$?"
check  "expand in quotes"             'echo "$HOME"'
check  "single no expand"             "echo '\$HOME'"
check  "dollar alone"                 "echo \$"
check  "dollar digit"                 "echo \$1"
check  "expand concat"                "echo \${HOME}x"
vcheck "very long expansion"          "echo \$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME\$HOME"

# ══════════════════════════════════════════════
section "[6] BUILTINS — echo"
# ══════════════════════════════════════════════
check  "echo basic"                   "echo hello"
check  "echo -n"                      "echo -n hello"
check  "echo -n -n"                   "echo -n -n"
check  "echo multiple args"           "echo a b c d e"
check  "echo empty"                   "echo"
check  "echo empty quotes"            "echo '' \"\""

# ══════════════════════════════════════════════
section "[7] BUILTINS — cd"
# ══════════════════════════════════════════════
check  "cd no arg"                    "cd"
check  "cd /"                         "cd /"
check  "cd nonexist"                  "cd /nonexistent_xyz_abc"
check  "cd dotdot"                    "cd .."
check  "cd dot"                       "cd ."
check  "cd trop d'args"               "cd /tmp /var"
check  "cd empty string"              "cd ''"
check  "cd sans HOME"                 "unset HOME"
vcheck "cd /tmp clean"                "cd /tmp"
vcheck "cd nonexist leak"             "cd /nonexistent_xyz"

# ══════════════════════════════════════════════
section "[8] BUILTINS — export"
# ══════════════════════════════════════════════
check  "export no args"               "export"
vcheck "export simple"                "export _VG_A=hello"
vcheck "export empty val"             "export _VG_A="
vcheck "export no val"                "export _VG_A"
check  "export invalid chiffre"       "export 1BAD=val"
check  "export invalid ="             "export =badval"
check  "export invalid tiret"         "export bad-name=val"
check  "export invalid @"             "export bad@name=val"
vcheck "export quoted val"            "export _VG_A=\"hello world\""
vcheck "export single quotes val"     "export _VG_A='hello'"
vcheck "export empty dbl"             "export _VG_A=\"\""
vcheck "export empty sgl"             "export _VG_A=''"

# Export + quotes (bug connu — échoue jusqu'à fix)
check  "export dbl wraps singles vides"  $'export _A="\'\'"\necho $_A'
check  "export dbl wraps single mot"     $'export _A="\'hello\'"\necho $_A'
check  "export dbl singles vides+\$USER" $'export _A="\'\'$USER\'\'"\necho $_A'
check  "export dbl \$USER entre singles" $'export _A="\'$USER\'"\necho $_A'
check  "export sgl contient dbl quotes"  $'export _A='"'"'""'"'"'\necho $_A'
check  "export sgl wraps dbl mot"        $'export _A='"'"'"hello"'"'"'\necho $_A'
check  "export alternance sgl dbl"       $'export _A='"'"'a'"'"'"b"'"'"'c'"'"'\necho $_A'
check  "export alternance dbl sgl"       $'export _A="a"'"'"'b'"'"'"c"\necho $_A'
check  "export singles+var milieu"       $'export _A="\'\'$USER"\necho $_A'
check  "export var+singles fin"          $'export _A="$USER\'\'"\necho $_A'
check  "export 4 singles vides"          $'export _A="\'\'\'\'"\necho $_A'
check  "export singles intercalés"       $'export _A="a\'b\'c\'d"\necho $_A'
check  "export overwrite avec quotes"    $'export _A="\'old\'"\nexport _A="\'new\'"\necho $_A'
check  "export puis unset"              $'export _A="\'val\'"\nunset _A\necho $_A'

# ══════════════════════════════════════════════
section "[9] BUILTINS — unset"
# ══════════════════════════════════════════════
check  "unset no args"                "unset"
check  "unset nonexist"               "unset NONEXIST_VAR_ZZZ"
check  "unset invalid chiffre"        "unset 1BAD"
check  "unset invalid tiret"          "unset bad-name"
vcheck "unset HOME"                   "unset HOME"
vcheck "unset existing"               "unset PATH"

# ══════════════════════════════════════════════
section "[10] BUILTINS — exit"
# ══════════════════════════════════════════════
check  "exit arg non numérique"       "exit abc"
check  "exit arg alphanum"            "exit 1abc"
check  "exit trop d'args"             "exit 1 2 3"
vcheck "exit 0"                       "exit 0"
vcheck "exit 1"                       "exit 1"
vcheck "exit 42"                      "exit 42"
vcheck "exit 126"                     "exit 126"
vcheck "exit 127"                     "exit 127"
vcheck "exit sans arg"                "exit"

# ══════════════════════════════════════════════
section "[11] BUILTINS — env / pwd"
# ══════════════════════════════════════════════
vcheck "env"                          "env"
vcheck "pwd"                          "pwd"
check  "pwd with args"                "pwd /tmp"

# ══════════════════════════════════════════════
section "[12] COMMANDES INTROUVABLES / PERMISSIONS"
# ══════════════════════════════════════════════
check  "cmd inexistant"               "thiscmddoesnotexist"
check  "./relatif inexistant"         "./nonexistent_xyz"
check  "chemin absolu inexistant"     "/nonexistent_xyz"
touch /tmp/ra_noperm.sh && chmod 000 /tmp/ra_noperm.sh
check  "exec sans permission (exit 126)" "/tmp/ra_noperm.sh"
chmod 644 /tmp/ra_noperm.sh
check  "exec non exécutable 644"      "/tmp/ra_noperm.sh"
rm -f /tmp/ra_noperm.sh

# ══════════════════════════════════════════════
section "[13] SANS PATH / ENV VIDE"
# ══════════════════════════════════════════════
vcheck "echo sans PATH"               "echo hello"                     "HOME=/tmp"
vcheck "cmd not found sans PATH"      "ls"                             "HOME=/tmp"
vcheck "pipe absolu sans PATH"        "/bin/echo hi | /bin/cat"        "HOME=/tmp"
vcheck "pipe cmd not found sans PATH" "ls | cat"                       "HOME=/tmp"
vcheck "export sans PATH"             "export _VG_B=hello"             "HOME=/tmp"
vcheck "env vide echo"                "echo hello"                     ""
vcheck "env vide cmd not found"       "ls"                             ""
vcheck "env vide pipe absolu"         "/bin/echo hi | /bin/cat"        ""
vcheck "env vide redir"               "/bin/echo hi > /tmp/ra_ev.txt"  ""
vcheck "env vide heredoc"             $'/bin/cat <<EOF\nhello\nEOF'    ""
vcheck "env vide exit"                "exit 0"                         ""

# ══════════════════════════════════════════════
section "[14] EDGE CASES"
# ══════════════════════════════════════════════
vcheck "empty input"                  ""
vcheck "only spaces"                  "   "
vcheck "glob star"                    "echo *"
vcheck "tilde"                        "echo ~"
vcheck "slash cmd"                    "/bin/echo hello"
vcheck "very long cmd"                "echo $(python3 -c "print('a'*5000)")"
vcheck "many args"                    "$(python3 -c "print('echo ' + ' '.join(['arg']*300))")"
vcheck "null cmd quotes"              "\"\""
vcheck "dollar question pipe"         "false | echo \$?"

# ══════════════════════════════════════════════
section "[15] TESTS REPOS ETUDIANTS — CRASH / SEGFAULT"
# ══════════════════════════════════════════════

# ── Segfault bait (mini_death / parsing_hell) ──
check  "echo <| echo"                 "echo |< echo segf"
check  "echo >| echo"                 "echo segf >| echo is this invalid"
check  "echo > > < echo"             'echo > > < "echo"'
check  "echo > > | echo"             "echo > > | echo kekw"
check  "echo < < > echo"             "echo < < > echo"
check  "echo < < < > ok"             "echo < < < > ok"
check  "echo < < | echo"             "echo < < | echo ok"
check  "echo < < | < ok"             "echo < < | < ok"
check  "echo < < | > echo"           "echo < < | > echo"
check  "echo >>| echo"               "echo >>| echo super valid"
check  "echo >>< echo"               'echo >>< "echo"'
check  "echo <<| echo"               "echo <<| echo ok"
check  "echo <<|< ok"                "echo <<|< ok"
check  "echo <<|> echo"              "echo <<|> echo"
check  "echo <<> echo"               "echo <<> echo"
check  "echo <<<> ok"                "echo <<<> ok"
check  "echo seg < > echo"           "echo seg < > echo seg"
check  "echo seg > < echo"           "echo seg > < echo segf"
check  "echo seg < < > echo"         "echo seg < < > echo segf"
check  "echo | > la"                 "echo | > la"
check  "<| echo ok"                  "<| echo ok"
check  ">>| echo wtf"                ">>| echo wtf"
check  ">| echo wtf"                 ">| echo wtf"
check  "<| echo wtf"                 "<| echo wtf"
check  "<<| echo wtf"                "<<| echo wtf"

# ── Quotes folles sur le nom de commande ──
vcheck "commande tout-quotes"         'p""'"'''"'w'"''''''""""""'"''"''"''"''"''"''"''"''"''"''"''"''"''"''"''"''"''"''"''"'d"
vcheck "echo vide + ok"              "''echo ok"
vcheck "echo dbl vide + ok"          '""echo ok'
vcheck "cmd entre doubles"           '"echo" 42'
vcheck "cmd entre singles"           "'echo' 42"
vcheck "ls entre singles/doubles"    "''''''\"ls\"''''''"
vcheck "echo flag quote"             'echo -n"-n" bonjour'

# ── Exit cas extrêmes ──
check  "exit très grand positif"      "exit 9223372036854775807"
check  "exit overflow positif"        "exit 9223372036854775808"
check  "exit très grand négatif"      "exit -9223372036854775808"
check  "exit overflow négatif"        "exit -9223372036854775809"
check  "exit infini positif"          "exit 9999999999999999999999999999999999"
check  "exit infini négatif"          "exit -9999999999999999999999999999999999"
check  "exit +42"                     "exit +42"
check  "exit -42"                     "exit -42"
check  "exit +0"                      "exit +0"
check  "exit -0"                      "exit -0"
check  "exit 00000...1"               "exit 00000000000000000000000000000000001"
check  "exit 00000...0"               "exit 00000000000000000000000000000000000"
check  "exit 42 abc"                  "exit 42 abc"
check  "exit abc 42"                  "exit abc 42"
check  "exit 123\"123\""             'exit 123"123"'
check  "exit ' 5'"                    "exit ' 5'"
check  "exit '5 '"                    "exit '5 '"
check  "exit '5  x'"                  "exit '5     x'"
check  "exit _0"                      "exit _0"
check  "exit 0_"                      "exit 0_"
check  "exit +"                       "exit +"
check  "exit -"                       "exit -"
check  "exit ++"                      "exit ++"
check  "exit --"                      "exit --"
check  "exit +++"                     "exit +++"
check  "exit ---"                     "exit ---"
check  "exit 5 < infile"              "exit 5 < /dev/null"

# ── Export cas extrêmes ──
check  "export A==a"                  $'export A==a\necho $A'
check  "export A===a"                 $'export A===a\necho $A'
check  "export A=a=a=a"              $'export A=a=a=a=a=a\necho $A'
check  "export long chain"            "export A=a B=b C=c D=d E=e F=f G=g H=h I=i J=j"
check  "export T=>> puis \$T"         $'export T=">>"\n$T lol'
check  "export T=| puis \$T"          $'export T="|"\necho segfault $T grep segfault'
check  "export T=< puis \$T"          $'export T="<"\necho segfault $T grep segfault'
check  "export T=<< puis \$T"         $'export T="<<"\necho segfault $T grep segfault'
check  "export T=| \$T\$T\$T"         $'export T="|"\n$T$T$T$T$T$T$T'
check  "export \$?"                   "export \$?"
check  "export ?=val"                 "export ?=val"
check  "export ''=''"                 "export ''=''"
check  "export \"\"=\"\""             'export ""=""'
check  "export ="                     "export ="
check  "export =============="        "export =============="
check  "export +++++++=123"           "export +++++++=123"

# ── Cd cas extrêmes ──
check  "cd --"                        "cd --"
check  "cd +"                         "cd +"
check  "cd ?"                         "cd ?"
check  "cd //////"                    "cd //////"
check  "cd ./././"                    "cd ./././"
check  "cd trop profond"              "cd ../../../../../../../../../../../../../../.."
check  "cd arg invalide"              "cd bark bark"

# ── Variables extrêmes ──
check  "echo \$\$"                    "echo \$\$"
check  "echo \$\$\$"                  "echo \$\$\$"
check  "echo \$U/SER"                 "echo \$U/SER"
check  "echo \$/ \$/"                 "echo \$/ \$/"
check  "\$? seul"                     "\$?"
check  "echo \$USER42"               "echo \$USER42"
check  "echo \$USER\$"               "echo \$USER\$"
check  "echo hello\$NOT \$USER"      "echo hello \$NOT_A_VAR \$NOT_A_VAR \$USER"

# ── Echo cas extrêmes ──
check  "echo -nnnnnnnnnn"             "echo -nnnnnnnnnn"
check  "echo -n -nnn -nnnnn"          "echo -n -nnn -nnnnn feel my pain"
check  "echo -n -n -n-n"             "echo -n -n -n-n"
check  "echo -"                       "echo -"
check  "echo --"                      "echo --"
check  "ECHO majuscule"               "ECHO hello"
check  "Echo mixte"                   "Echo hello"
check  "ec\"\"ho"                     'ec""ho test'
check  "ec''ho"                       "ec''ho test"
check  "\"\"echo"                     '""echo test'
check  "''echo"                       "''echo test"
check  "echo\"\" test"                'echo"" test'
check  "echo '' \"\" ''"             "echo '' \"\" '' test"
check  "echo a '' b '' c"            "echo a '' b '' c"

# ── Pipes extrêmes du repo ──
check  "echo | echo | echo | grep"   "echo 42 | echo no | echo smth | grep 42"
check  "pipe sleep 0 10x"             "sleep 0 | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat | cat"
check  "pipe cmd invalide milieu"     "cat infile_none | x | grep dream | wc -l"
check  "pipe exit dans pipe"         "exit 1 | exit 0"
check  "exit | ls"                    "exit | ls"
check  "ls | exit"                    "ls | exit"
check  "ls | exit 42"                 "ls | exit 42"
check  "cat | cat | ls"              "cat | cat | ls"

# ── Heredoc extrêmes ──
vcheck "heredoc delim var"            $'cat << $USER\nwhy\nnot\n$USER'
vcheck "heredoc delim quotes mix"     $'cat << "$US"E"R"\nbecause\nwe\nlove\nbash\n$USER'
vcheck "heredoc pipe gauche"          $'ls | cat << stop | grep "asd"\nstop'
check  "heredoc + redirect combo"     $'cat << here -e\nhello\nhere'
check  "<< echo oi"                   "<< echo oi"

# ── Syntax errors repo ──
check  "| seul"                       "|"
check  "|| seul"                      "||"
check  "||| seul"                     "|||"
check  "pipe vide | |"                "ls | | cat"
check  "pipe faux gauche"             "| fake_cmd"
check  "pipe faux droite"             "fake_cmd |"
check  "fake || ls"                   "fake_cmd || ls"
check  "ls | < pipe"                  "ls | <"
check  "ls | << pipe"                 "ls | <<"
check  "ls | > pipe"                  "ls | >"
check  "ls | >> pipe"                 "ls | >>"
check  "ls > > "                      "ls > >"
check  "ls > >> "                     "ls > >>"
check  "ls > < "                      "ls > <"
check  "ls >> > "                     "ls >> >"
check  "ls << < "                     "ls << <"
check  "echo hello | ;"              "echo hello | ;"
check  "> > > > >"                   "> > > > >"
check  ">> >> >> >>"                  ">> >> >> >>"
check  "< < < < < <"                  "< < < < < <"
check  "EechoE"                       "EechoE"
check  ".echo."                       ".echo."
check  ">echo>"                       ">echo>"
check  "<echo<"                       "<echo<"
check  "|echo|"                       "|echo|"
check  "| test"                       "| test"
check  "| | | | test"                "| | | | test"
check  "||||||||"                     "||||||||"
check  "<>"                           "<>"
check  "< >"                          "< >"
check  "unset \$HOME"                 "unset \$HOME"

# ══════════════════════════════════════════════
section "[16] FILESYSTEM — DOSSIER/FICHIER SUPPRIMÉ SOUS LES PIEDS"
# ══════════════════════════════════════════════

# Nettoyage préalable des dirs de test
rm -rf /tmp/ms_fs_a /tmp/ms_fs_b /tmp/ms_fs_c /tmp/ms_fs_d /tmp/ms_fs_e \
       /tmp/ms_fs_f /tmp/ms_fs_g /tmp/ms_fs_h /tmp/ms_fs_vg1 /tmp/ms_fs_vg2 \
       /tmp/ms_fs_vg3 /tmp/ms_fs_vg4 /tmp/ms_fs_vg5

# ── cd dans un dossier puis le supprimer ──
check  "mkdir+cd+rm+pwd"              $'mkdir /tmp/ms_fs_a\ncd /tmp/ms_fs_a\nrm -rf /tmp/ms_fs_a\npwd'
check  "mkdir+cd+rm+ls"               $'mkdir /tmp/ms_fs_b\ncd /tmp/ms_fs_b\nrm -rf /tmp/ms_fs_b\nls'
check  "mkdir+cd+rm+cd .."            $'mkdir /tmp/ms_fs_c\ncd /tmp/ms_fs_c\nrm -rf /tmp/ms_fs_c\ncd ..'
check  "mkdir+cd+rm+echo ok"          $'mkdir /tmp/ms_fs_d\ncd /tmp/ms_fs_d\nrm -rf /tmp/ms_fs_d\necho ok'
check  "mkdir+cd+rm+echo \$PWD"       $'mkdir /tmp/ms_fs_e\ncd /tmp/ms_fs_e\nrm -rf /tmp/ms_fs_e\necho $PWD'
check  "mkdir+cd+rm+export+echo"      $'mkdir /tmp/ms_fs_f\ncd /tmp/ms_fs_f\nrm -rf /tmp/ms_fs_f\nexport X=hello\necho $X'

# ── Nesting : mkdir a/b, cd a/b, rm -rf a ──
check  "mkdir a/b+cd b+rm a+pwd"      $'mkdir -p /tmp/ms_fs_g/b\ncd /tmp/ms_fs_g/b\nrm -rf /tmp/ms_fs_g\npwd'
check  "mkdir a/b+cd b+rm a+ls"       $'mkdir -p /tmp/ms_fs_h/b\ncd /tmp/ms_fs_h/b\nrm -rf /tmp/ms_fs_h\nls'
check  "mkdir a/b/c+cd c+rm a+cd .."  $'mkdir -p /tmp/ms_fs_a/b/c\ncd /tmp/ms_fs_a/b/c\nrm -rf /tmp/ms_fs_a\ncd ..'
check  "mkdir a/b/c+cd c+rm a+pwd"    $'mkdir -p /tmp/ms_fs_b/b/c\ncd /tmp/ms_fs_b/b/c\nrm -rf /tmp/ms_fs_b\npwd'

# ── Fichier créé puis supprimé ──
check  "créer fichier+rm+cat"         $'echo hello > /tmp/ms_fs_file1\nrm /tmp/ms_fs_file1\ncat /tmp/ms_fs_file1'
check  "créer+cat+rm+cat"             $'echo world > /tmp/ms_fs_file2\ncat /tmp/ms_fs_file2\nrm /tmp/ms_fs_file2\ncat /tmp/ms_fs_file2'
check  "redir vers fichier+rm+redir"  $'echo a > /tmp/ms_fs_file3\nrm /tmp/ms_fs_file3\necho b > /tmp/ms_fs_file3\ncat /tmp/ms_fs_file3'
check  "heredoc+rm+cat"               $'cat <<EOF > /tmp/ms_fs_file4\nhello\nEOF\nrm /tmp/ms_fs_file4\ncat /tmp/ms_fs_file4'

# ── pipe dans un dossier supprimé ──
check  "cd+rm+pipe echo|cat"          $'mkdir /tmp/ms_fs_c\ncd /tmp/ms_fs_c\nrm -rf /tmp/ms_fs_c\necho hi | cat'
check  "cd+rm+redir vers fichier"     $'mkdir /tmp/ms_fs_d\ncd /tmp/ms_fs_d\nrm -rf /tmp/ms_fs_d\necho hi > outfile'
check  "cd+rm+pipe+redir"             $'mkdir /tmp/ms_fs_e\ncd /tmp/ms_fs_e\nrm -rf /tmp/ms_fs_e\necho hi | cat > outfile2'

# ── cd dans dir supprimé puis cd ailleurs ──
check  "cd+rm+cd /tmp"                $'mkdir /tmp/ms_fs_f\ncd /tmp/ms_fs_f\nrm -rf /tmp/ms_fs_f\ncd /tmp\npwd'
check  "cd+rm+cd HOME"                $'mkdir /tmp/ms_fs_g\ncd /tmp/ms_fs_g\nrm -rf /tmp/ms_fs_g\ncd\npwd'

# ── Leak valgrind — dossier supprimé ──
vcheck "vg: mkdir+cd+rm+pwd"         $'mkdir /tmp/ms_fs_vg1\ncd /tmp/ms_fs_vg1\nrm -rf /tmp/ms_fs_vg1\npwd'
vcheck "vg: mkdir a/b+cd b+rm a"     $'mkdir -p /tmp/ms_fs_vg2/b\ncd /tmp/ms_fs_vg2/b\nrm -rf /tmp/ms_fs_vg2\npwd'
vcheck "vg: cd+rm+echo ok"           $'mkdir /tmp/ms_fs_vg3\ncd /tmp/ms_fs_vg3\nrm -rf /tmp/ms_fs_vg3\necho ok'
vcheck "vg: cd+rm+pipe"              $'mkdir /tmp/ms_fs_vg4\ncd /tmp/ms_fs_vg4\nrm -rf /tmp/ms_fs_vg4\necho hi | cat'
vcheck "vg: fichier+rm+cat"          $'echo hi > /tmp/ms_fs_vg5\nrm /tmp/ms_fs_vg5\ncat /tmp/ms_fs_vg5'

# Nettoyage post-section
rm -rf /tmp/ms_fs_a /tmp/ms_fs_b /tmp/ms_fs_c /tmp/ms_fs_d /tmp/ms_fs_e \
       /tmp/ms_fs_f /tmp/ms_fs_g /tmp/ms_fs_h /tmp/ms_fs_file1 /tmp/ms_fs_file2 \
       /tmp/ms_fs_file3 /tmp/ms_fs_file4

# ══════════════════════════════════════════════
echo -e "\n${CYAN}================================================================${NC}"
echo -e "${CYAN}  RECAP GLOBAL${NC}"
echo -e "${CYAN}================================================================${NC}"
echo -e "${GREEN}PASS   : $TOTAL_PASS${NC}"
echo -e "${YELLOW}WARN   : $TOTAL_WARN${NC}"
echo -e "${RED}FAIL   : $TOTAL_FAIL${NC}"
echo -e "${RED}LEAKS  : $TOTAL_LEAK${NC}"
echo -e "${RED}CRASH  : $TOTAL_CRASH${NC}"

log ""
log "════════════════════════════════════════════════════"
log "  RECAP GLOBAL  ($(date '+%Y-%m-%d %H:%M:%S'))"
log "════════════════════════════════════════════════════"
log "  TOTAL TESTS : $TEST_NUM"
log "  PASS        : $TOTAL_PASS"
log "  FAIL        : $TOTAL_FAIL"
log "  LEAKS       : $TOTAL_LEAK"
log "  CRASH       : $TOTAL_CRASH"
log ""

# Nettoyage /tmp
rm -f /tmp/ra_out.txt /tmp/ra_app.txt /tmp/ra_m1.txt /tmp/ra_m2.txt \
      /tmp/ra_pr.txt /tmp/ra_ev.txt

# Nettoyage des fichiers créés dans le répertoire courant pendant les tests
_AFTER_FILES=$(ls -1 . 2>/dev/null | sort)
_CREATED=$(comm -13 <(echo "$_BEFORE_FILES") <(echo "$_AFTER_FILES"))
if [ -n "$_CREATED" ]; then
	echo -e "${YELLOW}[cleanup] fichiers créés par les tests — supprimés :${NC}"
	while IFS= read -r f; do
		echo -e "  ${YELLOW}$f${NC}"
		rm -f "$f"
	done <<< "$_CREATED"
fi
