/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_list.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbax <jbax@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/27 16:24:43 by jbax          #+#    #+#                 */
/*   Updated: 2023/03/02 17:19:09 by avon-ben      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_LIST_H
# define SIGNAL_LIST_H

static const char *signals[17] = {
     "",
	"Hangup: 1",
	"",
	"Quit: 3",
     "Illegal instruction: 4",
     "Trace/BPT trap: 5",
	"Abort trap: 6",
     "EMT trap: 7",
     "Floating point exception: 8",
	"Killed: 9",
     "Bus error: 10",
     "Segmentation fault: 11",
     "Bad system call: 12",
     "",
     "Alarm clock: 14",
     "Terminated: 15",
	0,
};

#endif

/*
     1     SIGHUP       terminate process    terminal line hangup
     2     SIGINT       terminate process    interrupt program
     3     SIGQUIT      create core image    quit program
     4     SIGILL       create core image    illegal instruction
     5     SIGTRAP      create core image    trace trap
     6     SIGABRT      create core image    abort program (formerly SIGIOT)
     7     SIGEMT       create core image    emulate instruction executed
     8     SIGFPE       create core image    floating-point exception
     9     SIGKILL      terminate process    kill program
     10    SIGBUS       create core image    bus error
     11    SIGSEGV      create core image    segmentation violation
     12    SIGSYS       create core image    non-existent system call invoked
     13    SIGPIPE      terminate process    write on a pipe with no reader
     14    SIGALRM      terminate process    real-time timer expired
     15    SIGTERM      terminate process    software termination signal
     16    SIGURG       discard signal       urgent condition present on
                                             socket
     17    SIGSTOP      stop process         stop (cannot be caught or
                                             ignored)
     18    SIGTSTP      stop process         stop signal generated from
                                             keyboard
     19    SIGCONT      discard signal       continue after stop
     20    SIGCHLD      discard signal       child status has changed
     21    SIGTTIN      stop process         background read attempted from
                                             control terminal
     22    SIGTTOU      stop processeof         background write attempted to
                                             control terminal
     23    SIGIO        discard signal       I/O is possible on a descriptor
                                             (see fcntl(2))
     24    SIGXCPU      terminate process    cpu time limit exceeded (see
                                             setrlimit(2))
     25    SIGXFSZ      terminate process    file size limit exceeded (see
                                             setrlimit(2))
     26    SIGVTALRM    terminate process    virtual time alarm (see
                                             setitimer(2))
     27    SIGPROF      terminate process    profiling timer alarm (see
                                             setitimer(2))
     28    SIGWINCH     discard signal       Window size change
     29    SIGINFO      discard signal       status request from keyboard
     30    SIGUSR1      terminate process    User defined signal 1
     31    SIGUSR2      terminate process    User defined signal 2*/