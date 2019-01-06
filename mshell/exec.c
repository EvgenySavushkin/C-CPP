#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "exec.h"

void add_elem (intlist **f, int pid) 
{
    intlist *cur;
    if ((*f) == NULL) {
        *f = (intlist *) malloc(sizeof(intlist));
        cur = *f;   
    }
    else {
        cur = *f;
        while (cur -> next != NULL) {
            cur = cur -> next;
        }
        cur -> next = (intlist *) malloc(sizeof(intlist));
        cur = cur -> next;
    }
    cur -> pid = pid;
    cur -> next = NULL;
}

void print_intlist(intlist *f) 
{
    while(f != NULL) {
        fprintf(stderr, "%d\n", f -> pid);
        f = f -> next;
    }
}

void clear_intlist(intlist *f) 
{
    intlist *cur;
    cur = f;
    while (cur != NULL) {
        cur = cur -> next;
        free(f);
        f = cur;
    }
}

/*void clear_zombie(intlist *b)
{
    int pid, status;
    while (b != NULL) {
        if (b -> pid == -1) {
            b = b -> next;
            continue;
        }
        pid = waitpid(b -> pid, &status, WNOHANG);
        if (pid != 0) {
            b -> pid = -1;         
        }
        b = b -> next;
    }
}*/

void clear_zombie(intlist **b)
{
	int pid, status;
	intlist *cur, *tmp;
	cur = *b;
	while (cur != NULL) {
		pid = waitpid(cur -> pid, &status, WNOHANG);
		if (pid != 0) {
			*b = (*b) -> next;
			free(cur);
			cur = *b;
		}
		else {
			break;
		}
	}
	if (cur == NULL) {
		return;
	}
	tmp = cur;
	cur = cur -> next;
    while (cur != NULL) {
        pid = waitpid(cur -> pid, &status, WNOHANG);
        if (pid != 0) {
         	tmp -> next = cur -> next;
         	free(cur);
         	cur = tmp -> next;            
        }
        else {
        	cur = cur -> next;
        	tmp = tmp -> next;
        }
    }
}

int is_com(tree *t) 
{
    char *s;
    s = t -> argv[0];
    if (!strcmp(s, "cd") || !strcmp(s, "clear") || !strcmp(s, "exit")) {
        return 1;
    }
    return 0;
}

int exec_cd(tree *t) 
{
    if (t -> argv[1] == NULL) {
        chdir(getenv("HOME"));
        return 0;
    }
    if (chdir(t -> argv[1]) == -1) {
        fprintf(stderr, "cd: %s: no shuch file or directory\n", t -> argv[1]);
        return 1;
    }
    return 0;
}

/*
int exec_wc(tree *t)
{
	FILE *fp;
	int j, slov, strok, bukv, bukv_a;
	char a;
	int fd;
	int fs;
//	if(in!=-1)dup2(in,0);
//	if(out!=-1)dup2(out,1);
//	printf("in %i, out %i", in,out);
	int pid = 1;	
	if (t -> outfile != NULL) 
	{
		int  status;
		if((pid=fork())==0)
		{
			fd = open(t -> outfile, O_WRONLY | O_CREAT | (t -> append ? O_APPEND : O_TRUNC), 0666);
        		if (fd == -1) 
			{
            			perror("open");
            			exit(1);
      	  		}
			dup2(fd,1);
		} else {waitpid(pid, &status, 0);printf("jdu\n");return 0;}}

			if (t-> argv[1] == NULL)
			{
				
				a = fgetc(stdin);a++;fputc(a,stdout);
				//fprintf(stdout, "lol=%d\n",a);
				fprintf(stdout, "net faila\n");
			        //freopen("/dev/null","w",stdout);
	 		        close(fd);if(pid==0)exit(0);return(0);
			}
	
			if ((fp = fopen (t->argv[1],"r"))!=NULL)
			{
	   		    	 slov =0;strok=0;bukv=0;bukv_a=0;
	   			 a=fgetc(fp);
   	 		 	 while(a!=EOF)
	   			 {
          		  		    if (a == ' '||a=='\n') slov += 1;
    					    if (a == '\n') strok += 1;
     		 		            if (a == 'a')  bukv_a +=1;
        				    if (a != ' ' && a != '\n') bukv += 1;	    
					    a=fgetc(fp);
			   	 }
	  		  	 fclose(fp);
	 		 	 fprintf(stdout,"vsego %i slov, %i strok, %i bukv, %i bukv_a \n",slov,strok,bukv,bukv_a);
	   		         close(fd);if(pid==0)exit(0);return 0;
			}
	
			fprintf(stderr, "wc: %s: no such file or directory\n", t->argv[1]);	
			close(fd);if(pid==0)exit(1);return 1;
}
*/


int exec_clear()
{
    write(1, "\033[2J\033[H", sizeof("\033[2J\033[H"));
    return 0;
}

int exec_exit()
{
	exit_val = 1;
	longjmp(begin, 1);
	return 0;
}

int sh_com(tree *t)
{
    char *s;
    s = t -> argv[0];
    if (!strcmp(s, "cd")) {
        return exec_cd(t);
    }
    if (!strcmp(s, "clear")) {
        return exec_clear();
    }
    if (!strcmp(s, "exit")) {
        return exec_exit();
    }
//    if (!strcmp(s, "wc")){
//	    	return exec_wc(t);
//    }
    return 1;
}

int my_sh_com(tree *t,int in,int out)
{
	char *s;
	s = t -> argv[0];
	if (!strcmp(s,"wc")){
//		return exec_wc(t,in,out);
	}
	return 1;
}

void chng_iofiles(int in, int out, tree *t)
{
    int fd;
/*    if (in != -1) {
        dup2(in, 0);
	printf("chin\n");
        close(in);
    }
    if (out != -1) {
        dup2(out, 1);
	printf("chout\n");
        close(out);
    }*/
    if (t -> infile != NULL) {
        if ((fd = open(t -> infile, O_RDONLY)) == -1) {
            perror("open");
            exit(1);
        }
        dup2(fd, 0);            
        close(fd);
    }
    if (t -> outfile != NULL) {
        fd = open(t -> outfile, O_WRONLY | O_CREAT | (t -> append ? O_APPEND : O_TRUNC), 0666);
        if (fd == -1) {
            perror("open");
            exit(1);
        }
        dup2(fd, 1);
        close(fd);
    }
//    printf("chng\n");
}

int exec_com_sh(tree * t)
{
    return exec_com_list(t, 0);
}

int exec_com_list(tree *t, int p)
{
    int ret, to_do;
    ret = exec_conv(t, p);
    while (t -> next != NULL) {
        to_do = 1;
        if (t -> type == AND && ret) {
            to_do = 0;
        }
        else if (t -> type == OR && !ret) {
            to_do = 0;
        }
        t = t -> next;
        if (to_do) {
            ret = exec_conv(t, p);
        }
    }
    return ret;
}


int exec_conv(tree *t, int p)
{
    int ret, in, out,out1, next_in,next1_in, status ;
    int fd[2];
    intlist *frgrnd = NULL;
//    if (t -> pipe == NULL) {
//        return exec_command(t, -1, -1, -1, p, &frgrnd);
//    }
    next_in = -1;
    	next1_in = -1;//my
    int pid, stts;
//    if (t->pipe != NULL){ //
	    if((pid=fork())==0){//
    while (t -> pipe != NULL) {
        pipe(fd);
        //in = next_in;
        next1_in = fd[0];
        out1 = fd[1];
//		dup2(out1,1);close(out1);//
//       	        ret = exec_command(t, in, out, next_in, 1, &frgrnd);
		//dup2(out1,1);close(out1);
		if((pid=fork())==0)
		{
		dup2(out1,1);close(out1);close(next1_in);
		exec_command(t, in, out, next_in, 1, &frgrnd);
//		dup2(next1_in,0);close(next1_in);
//		t = t->pipe;
		}
		else{
		//if(g==1)next_in = -1;
		t=t->pipe;
		dup2(next1_in,0);close(next1_in);close(out1);//
//		waitpid(pid,&stts,0);
//        ret = exec_command(t, in, out, next_in, 1, &frgrnd);
//		waitpid(pid,&stts,0);//return ret;
//		exit(ret);
		} 
    }
    
//    printf("isp posl %s\n", t->argv[0]);
    ret = exec_command(t, -1, -1, -1, 1, &frgrnd);//chng -1 -> next_in
    	
//        exit(ret);
	}else{//
	waitpid(pid,&stts,0);return stts;
	}//}
    while(frgrnd != NULL) {
        waitpid(frgrnd -> pid, &status, 0); 
        frgrnd = frgrnd -> next;
    }
    clear_intlist(frgrnd);
    return ret;
}

int exec_command(tree *t, int in, int out, int next_in, int p, intlist **pfrgrnd) 
{
    int status, pid;
    if (t -> psubcmd == NULL) {
//	    printf("in %i, out %i\n", in, out);
        return exec_simple_com(t, in, out, next_in, p, pfrgrnd);
    }
    if ((pid = fork()) == 0) {
        clear_intlist(*pfrgrnd);
        chng_iofiles(in, out, t);
        if (next_in != -1) {
            close(next_in);
        }
        exec_com_list(t -> psubcmd, p);
        if (t -> backgrnd) {
            //in_bckgrnd_list(getpid());
        }
        exit(0);
    }
    else {
        if (t -> backgrnd) {
            waitpid(pid, &status, WNOHANG);
            add_elem(&bckgrnd, pid);
            if (WIFEXITED(status)) {
                return WEXITSTATUS(status);
            }
            return -1;
        }
        waitpid(pid, &status, 0);
        return 0;
    }
}

int exec_simple_com(tree *t, int in, int out, int next_in, int p, intlist **pfrgrnd) 
{
    int status, pid;
    if (is_com(t)) {
//	    printf("in %i, out %i\n",in, out);
//	    int lol = sh_com(t);//my
//	    if(next_in!= -1)exit(lol);//my
//	    else return lol;//my
        return sh_com(t);
//	return my_sh_com(t,in,out);
    }
//    if ((pid = fork()) == 0) {
        chng_iofiles(in, out, t);
//        close(next_in);
        
        execvp(t -> argv[0], t -> argv);printf("execpv %s\n",t->argv[0]);
        perror(t -> argv[0]);
        exit(1);
//    } 
    if (t -> backgrnd) {
        waitpid(pid, &status, WNOHANG);
        add_elem(&bckgrnd, pid);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
    }
    else if (p) {
        add_elem(pfrgrnd, pid);
        return 0;
    }
    else {      
        waitpid(pid, &status, 0);
    }
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
    return 1;
}
