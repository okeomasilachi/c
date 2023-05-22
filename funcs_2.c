#include "main.h"

/**
 * 
*/
static int environ_size()
{
	int count = 0;
	char **env;
	
	for (env = environ; *env != NULL; env++)
		count++;

	return count;
}

/**
 *
*/
int _updateenv(const char *name, const char *value)
{
	size_t name_len = _strlen(name), value_len = _strlen(value), old_value_len;
	char **env = environ, *new_env;

	for (env = environ; *env != NULL; env++)
	{
		if (_strncmp(name, *env, name_len) == 0 && (*env)[name_len] == '=')
		{
			old_value_len = _strlen(*env + name_len + 1);
			if (value_len <= old_value_len)
				_strcpy(*env + name_len + 1, value);
			else
			{
				new_env = (char *)malloc(name_len + value_len + 2);
				if (new_env == NULL)
					return -1;
				_strcpy(new_env, *env);
				_strcpy(new_env + name_len + 1, value);
				free(*env);
				*env = new_env;
			}
			return 0;
		}
	}
	return -1;
}

int _setenv(const char *name, const char *value, int overwrite)
{
	size_t name_len, value_len, new_var_len;
	char **env, **new_environ, **new_env, *new_var;
	int update_result;

	if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL)
		return -1;
	if (value == NULL)
		value = "";
	if (!overwrite)
		return _updateenv(name, value);
	update_result = _updateenv(name, value);
	if (update_result == 0)
		return 0;
	name_len = _strlen(name);
	value_len = _strlen(value);
	new_environ = (char **)malloc(sizeof(char *) * (environ_size() + 2));
	if (new_environ == NULL)
		return -1;
	new_env = new_environ;
	for (env = environ; *env != NULL; env++)
		*new_env++ = *env;

	new_var_len = name_len + value_len + 2;
	new_var = (char *)malloc(new_var_len);
	if (new_var == NULL)
	{
		free(new_environ);
		return -1;
	}
	_memcpy(new_var, name, name_len);
	new_var[name_len] = '=';
	_memcpy(new_var + name_len + 1, value, value_len);
	new_var[new_var_len - 1] = '\0';
	*new_env++ = new_var;
	*new_env = NULL;
	environ = new_environ;
	return 0;
}


/**
 *
*/
char *_getenv(const char *name)
{
	int name_len;
	char **env, *env_var;

	if (name == NULL || *name == '\0')
		return NULL;

	name_len = _strlen(name);
	for (env = environ; *env != NULL; env++)
	{
		env_var = *env;
		if (env_var == NULL || *env_var == '\0' || strchr(env_var, '=') == NULL)
			continue;
		if (_strncmp(name, env_var, name_len) == 0 && env_var[name_len] == '=')
			return &(env_var[name_len + 1]);
	}
	return NULL;
}

/**
 *
*/
int _unsetenv(const char *name)
{
	size_t name_len;
	char **env, **shift_env;

	if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL)
		return -1;
	name_len = _strlen(name);
	env = environ;
	while (*env != NULL)
	{
		if (_strncmp(name, *env, name_len) == 0 && (*env)[name_len] == '=')
			break;
		env++;
	}
	if (*env == NULL)
		return 0;
	shift_env = env;
	while (*shift_env != NULL)
	{
		*shift_env = *(shift_env + 1);
		shift_env++;
	}
	return 0;
}
