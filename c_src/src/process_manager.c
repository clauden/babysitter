#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "process_manager.h"

int pm_check_pid_status(pid_t pid)
{
  if (pid < 1) return -1; // Illegal
  return kill(pid, 0);
}

int pm_add_env(process_t **ptr, char* value)
{
  process_t *p = *ptr;
  // Expand space, if necessary
  if (p->env_c == p->env_capacity) {
    if (p->env_capacity == 0) p->env_capacity = 1;
    p->env = (char**)realloc(p->env, (p->env_capacity *= 2) * sizeof(char*));
  }
  p->env[p->env_c++] = strdup(value);
  return 0;
}

int pm_new_process(process_t **ptr)
{
  process_t *p = (process_t *) calloc(1, sizeof(process_t));
  if (!p) {
    perror("Could not allocate enough memory to make a new process.\n");
    return -1;
  }
  
  p->env_c = 0;
  p->env_capacity = 0;
  p->env = NULL;
  p->cd = NULL;
  
  p->command = NULL;
  p->before = NULL;
  p->after = NULL;
  
  *ptr = p;
  return 0;
}

int pm_free_process(process_t *p)
{
  if (p->command) free(p->command);
  if (p->before) free(p->before);
  if (p->after) free(p->after);
  if (p->cd) free(p->cd);
  
  int i = 0;
  for (i = 0; i < p->env_c; i++) free(p->env[i]);
  if (p->env) free(p->env);
  
  free(p);
  return 0;
}

// Privates
int pm_malloc_and_set_attribute(char **ptr, char *value)
{
  char *obj = (char *) calloc (sizeof(char), strlen(value) + 1);
  
  if (!obj) {
    perror("pm_malloc_and_set_attribute");
    return -1;
  }
  strncpy(obj, value, strlen(value));
  obj[strlen(value)] = (char)'\0';
  *ptr = obj;
  return 0;
}