/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedusser <jedusser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:39:55 by jean-michel       #+#    #+#             */
/*   Updated: 2024/09/02 15:03:41 by jedusser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "struct.h"

/*===========================builtins.c===============================*/

int		ft_exit(t_data *data, int last_status, int **fd, int last_fd);
int		ft_cd(t_data *data, int i);
char	*check_cd_args(t_data *data, char *new_dir);
int		ft_pwd(t_data *data);
int		ft_echo(t_data *data);
int		ft_env(t_data *data, int i);
int		ft_unset(t_data *data, int i);
void	set_env(char *key, char *value, char **env);

/*===========================export===============================*/

//export_utils
char	**add_to_table(t_table *table, char *new_var);
char	*create_quoted_var(char *key, char *value);
char	*create_unquoted_var(char *key, char *value);
char	*create_var_without_equals(char *key);
void	free_vars(t_vars *vars);
//export_update
int		process_env_var_for_export(t_vars *vars, char *env_var, t_data *data,
			int index);
int		process_full_entry(t_vars *vars, t_data *data, int i);
int		process_uncomplete_entry(t_vars *vars, t_data *data, int i);
//export_process
int		init_exported_env(t_data *data);
int		ft_export(t_data *data);
void	sort_tab(t_table *table);
void	update_table(char **table, int i, char *new_var);
int		process_unquoted_key(t_vars *vars, t_data *data, t_table *export,
			int i);

/*===========================builtins_utils.c===============================*/

int		is_builtin(t_data *data);
int		exec_builtin(t_data *data, int i, int **fd, int last_read);
int		is_numeric_str(char *str);
int		close_in_out_files(t_data *data);
void	handle_sigpipe(int sig);
