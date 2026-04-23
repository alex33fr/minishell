/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_temp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:52:24 by byonis            #+#    #+#             */
/*   Updated: 2026/04/23 12:13:36 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

#include <stdio.h>

int	main(int ac, char **av, char **envp)
{
	// char	*line = "< infile ls -l | wc -l > outfile";
	//					| arg1  | arg2 | arg3  |  arg4	|
	// "< infile" "ls -l" "|" "wc -l" "> outfile"
	
	
	// char	*line = "< infile \"ls -l\" | \"wc -l\" > outfile";
	// "< infile" ""ls -l"" "|" ""wc -l"" "> outfile"

	
	// char	*line = "echo \"|\"";
	// "echo \"|\""


	// char	*line = "echo \"\"";
	
	// char	*line = "echo \"hello\"world";

	// char	*line = "echo \"hello\"\'world\'";

	// char	*line = "echo \"\'hello\"";

	// char	*line = "echo ppp |       |  echo a";

	// char	*line = "ls > file1 > file2";

	// char	*line = "echo \"hello\" > file.txt world";
	
	// char	*line = "echo $HOME";
	
	// char	*line = "echo \"\'$HOME$PWD\'\"";

	char	*line = "echo \'$HOME\'";
	
	t_redir	*files_redir;
	t_queue	*tokens;
	t_cmd	*cmds;
	t_cmd	*temp;
	int		i;

	(void)ac;
	(void)av;
	tokens = lexer(line, envp); // rajouter last_status
	if (!tokens)
		return (1);
	cmds = create_cmds(tokens);
	if (!cmds)
		return (1);
	temp = cmds;
	while (temp)
	{
		i = 0;
		while (temp->args[i])
		{
			printf("%s\n", temp->args[i]);
			i++;
		}
		files_redir = temp->redir;
		while (files_redir)
		{
			printf("%s\n", files_redir->file);
			files_redir = files_redir->next;
		}
		temp = temp->next;
	}
	free_cmds(cmds);
	clear_queue(tokens);
	return (0);
}
