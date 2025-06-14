/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:31:21 by mben-cha          #+#    #+#             */
/*   Updated: 2025/06/14 16:31:38 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_redirect {
    int                 type; 
    char                *filename;
    struct s_redirect   *next;
}   t_redirect;

typedef struct s_cmd {
    char            **argv;
    t_redirect      *redirects;
    int             pipe_in;
    int             pipe_out;
    int             built_in;
    char            *path;
    struct s_cmd    *next;
}   t_cmd;

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);