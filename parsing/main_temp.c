/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_temp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byonis <byonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:52:24 by byonis            #+#    #+#             */
/*   Updated: 2026/04/01 15:28:52 by byonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

#include <stdio.h>

int	main(void)
{
	// char	line[33] = "< infile ls -l | wc -l > outfile";
	//					| arg1  | arg2 | arg3  |  arg4	|
	// "< infile" "ls -l" "|" "wc -l" "> outfile"
	
	
	// char	line[37] = "< infile \"ls -l\" | \"wc -l\" > outfile";
	// "< infile" ""ls -l"" "|" ""wc -l"" "> outfile"

	
	// char	line[8] = "echo \"|\"";
	// "echo \"|\""


	// char	line[7] = "echo \"\"";
	
	// char	*line = "echo \"hello\"world";

	char	*line = "echo \"hello";
	
	char	*temp;
	t_queue	*tokens;

	tokens = lexer(line);
	if (!tokens)
		return (1);
	while (tokens->front)
	{
		// printf("%d\n", tokens->front->token);
		dequeue(tokens, &temp);
		printf("%s\n", temp);
		free(temp);
	}
	clear_queue(tokens);
	return (0);
}
