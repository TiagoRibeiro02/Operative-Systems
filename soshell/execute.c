/*
   execute . cria um processo prog�nito e executa um programa
*/
#include "shell.h"
#include "sys/types.h"
#include "sys/wait.h"

int containsPipe(int numargs, char **args){
  int index;
  for (index = 0; index < numargs; index++)
    if(args[index][0] == '|')
    {
      return index;
    }
  return -1;
  
}


void execute (int numargs, char **args)
{
  int pid, pidFilho, status, fd[2];

  if ((pid = fork ()) < 0)
    { /* cria um processo progenito */
      perror ("forks");/* NOTE: perror() produz uma pequema mensagem de erro para o stream */
      exit (1);/* estandardizado de erros que descreve o ultimo erro encontrado */
               /* durante uma chamada ao sistema ou funcao duma biblioteca */
    }

  if (pid == 0)
    {
      int i = containsPipe(numargs, args);
      if (i==-1)
      {
        redirects(numargs, args);
        execvp (*args, args);
      }
      if (i > 0)
      {
        args[i] = NULL;
        pipe(fd);
        pidFilho = fork();

        if (pidFilho == 0) //write
        {
          numargs = i;
          redirects(numargs, args);
          dup2(fd[1], STDOUT_FILENO);
          close(fd[0]);
          close(fd[1]);
        }
        else{
          args = args + i + 1;
          numargs = numargs - i - 1;

          redirects(numargs, args);
          dup2(fd[0], STDIN_FILENO);
          close(fd[1]);
          close(fd[0]);
        }
        execvp(*args, args); //Chamar a função execpv() para executar os comandos agora ligados via um pipe.
        
      }
      
      

      execvp(*args, args);  /* NOTE: as versoes execv() e
                            * execvp() de execl() sao uteis quando */
      perror (*args);       /* o numero de argumentos nao e. conhecido.
                              * Os argumentos de  */
      exit (1);             /* execv() e execvp() sao o nome do ficheiro
                             * a ser executado e um */
    }                       /* vector de strings que contem os
                            * argumentos. O ultimo argument */

  while (wait (&status) != pid)
    /*spin fazer nada */ ;

  return;
}
