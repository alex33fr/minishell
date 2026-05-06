/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 12:32:17 by byonis            #+#    #+#             */
/*   Updated: 2026/05/05 10:15:26 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include "parsing.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <linux/limits.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "globals.h"
# include "parsing.h"
# include "runtime.h"

#endif
