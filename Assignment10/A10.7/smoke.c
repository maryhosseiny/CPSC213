#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"
#define NUM_ITERATIONS 1000
#ifdef VERBOSE
#define VERBOSE_PRINT(S, ...) printf(S, ##__VA_ARGS__)
#else
#define VERBOSE_PRINT(S, ...) ((void)0) // do nothing
#endif

// Additional variables
uthread_cond_t match_tobacco;
uthread_cond_t match_paper;
uthread_cond_t paper_tobacco;
int alert;
struct Agent
{
    uthread_mutex_t mutex;
    uthread_cond_t match;
    uthread_cond_t paper;
    uthread_cond_t tobacco;
    uthread_cond_t smoke;
};
struct Agent *createAgent()
{
    struct Agent *agent = malloc(sizeof(struct Agent));
    agent->mutex = uthread_mutex_create();
    agent->paper = uthread_cond_create(agent->mutex);
    agent->match = uthread_cond_create(agent->mutex);
    agent->tobacco = uthread_cond_create(agent->mutex);
    agent->smoke = uthread_cond_create(agent->mutex);
    return agent;
}
/**
* You might find these declarations helpful.
* Note that Resource enum had values 1, 2 and 4 so you can
combine resources;
* e.g., having a MATCH and PAPER is the value MATCH | PAPER ==
1 | 2 == 3
*/
enum Resource
{
    MATCH = 1,
    PAPER = 2,
    TOBACCO =
        4
};
char *resource_name[] = {"", "match", "paper", "", "tobacco"};
// # of threads waiting for a signal. Used to ensure that the
agent
    // only signals once all other threads are ready.
    int num_active_threads = 0;
int signal_count[5]; // # of times resource signalled
// [ ? Match Paper ? Smoke]
// i=0 i=1 i=2 i=3 i=4
int smoke_count[5]; // # of times smoker with resource smoked
// [ ? Match Paper ? Smoke]
// i=0 i=1 i=2 i=3 i=4
/**
* TODO: You will probably need to add some procedures and struct
etc.
**/
/**
 * First implementation:
 * MATCH|PAPER = 1|2 = 1 OR 2 = 3
 * MATCH|TOBACCO = 1|4 = 1 OR 4 = 5
 * PAPER|TOBACCO = 2|4 = 2 OR 4 = 6
 *
 * Second implementation:
 * MATCH+PAPER = 3
 * MATCH+TOBACCO = 5
 * PAPER+TOBACCO = 6
 **/
void wake_up(int s) {
  if (s == 1) { VERBOSE_PRINT ("Got matches, now waiting for another ingredient.\n"); }
  if (s == 2) { VERBOSE_PRINT ("Got paper, now waiting for another ingredient.\n"); }
  if (s == 4) { VERBOSE_PRINT ("Got tobbaco, now waiting for another ingredient.\n"); }
  if (s == 3) {
    uthread_cond_signal(match_paper);
    alert = 0;
    return;
  } 
  if (s == 5) {
    uthread_cond_signal(match_tobacco);
    alert = 0;
    return;
  } if (s == 6) {
    uthread_cond_signal(paper_tobacco);
    alert = 0;
    return;
  }
}

/**
* TOBACCO SMOKER
* > loop, attempting to smoke
* tries to acquire MATCH and PAPER
* must signal to agent after done smoking, to allow agent to
 produce more ingredients
*
**/
void *tobacco_smoker(void *av) {
  struct Agent *a = av;
  uthread_mutex_lock(a->mutex);
  while (1) {
    VERBOSE_PRINT("Tobacco smoker is waiting.\n");
    uthread_cond_wait(match_paper);
    VERBOSE_PRINT ("Tobacco smoker is done waiting, match andpaper available.\n");
    VERBOSE_PRINT ("Tobacco smoker is smoking.\n");
    uthread_cond_signal(a->smoke);
    smoke_count[TOBACCO]++;
  }
  uthread_mutex_unlock(a->mutex);
}

/**
* MATCH SMOKER
* > loop, attempting to smoke
* tries to acquire TOBACCO and PAPER
* must signal to agent after done smoking, to allow agent to
produce more ingredients
**/
void *match_smoker(void *av) {
  struct Agent *a = av;
  uthread_mutex_lock(a->mutex);
  while (1) {
    VERBOSE_PRINT("Match smoker is waiting.\n");
    uthread_cond_wait(paper_tobacco);
    VERBOSE_PRINT ("Match smoker is done waiting, tobacco and paper available.\n");
    VERBOSE_PRINT ("Match smoker is smoking.\n");
    uthread_cond_signal(a->smoke);
    smoke_count[MATCH]++;
  }
  uthread_mutex_unlock(a->mutex);
}

/**
* PAPER SMOKER
* > loop, attempting to smoke
* tries to acquire MATCH and TOBACCO
* must signal to agent after done smoking, to allow agent to
produce more ingredients
**/
void *paper_smoker(void *av) {
  struct Agent *a = av;
  uthread_mutex_lock(a->mutex);
  while (1) {
    VERBOSE_PRINT("Paper smoker is waiting.\n");
    uthread_cond_wait(match_tobacco);
    VERBOSE_PRINT ("Paper smoker is done waiting, tobacco and match available.\n");
    VERBOSE_PRINT ("Paper smoker is smoking.\n");
    uthread_cond_signal(a->smoke);
    smoke_count[PAPER]++;
  }
  uthread_mutex_unlock(a->mutex);
}

/*** TOBACCO LISTENER **/
void * tobacco_listener(void *av) {
  struct Agent *a = av;
  uthread_mutex_lock(a->mutex);
  while (1) {
    uthread_cond_wait(a->tobacco);
    alert = alert + TOBACCO;
    wake_up(alert);
  }
  uthread_mutex_unlock(a->mutex);
}

/*** MATCH LISTENER **/
void *match_listener(void *av) {
  struct Agent *a = av;
  uthread_mutex_lock(a->mutex);
  while (1) {
    uthread_cond_wait(a->match);
    alert = alert + MATCH;
    wake_up(alert);
  }
  uthread_mutex_unlock(a->mutex);
}

/*** PAPER LISTENER **/
void *paper_listener(void *av) {
  struct Agent *a = av;
  uthread_mutex_lock(a->mutex);
  while (1) {
    uthread_cond_wait(a->paper);
    alert = alert + PAPER;
    wake_up(alert);
  }
  uthread_mutex_unlock(a->mutex);
}


/**
* AGENT
* This is the agent procedure. It is complete and you shouldn't
change it in
* any material way. You can modify it if you like, but be sure
that all it does
* is choose 2 random resources, signal their condition variables,
and then wait
* wait for a smoker to smoke.
*/
void *agent(void *av)
{
    struct Agent *a = av;
    static const int choices[] = {MATCH | PAPER, MATCH | TOBACCO, PAPER | TOBACCO};
    static const int matching_smoker[] = {TOBACCO, PAPER,
                                          MATCH};
    srandom(time(NULL));
    uthread_mutex_lock(a->mutex);
    // Wait until all other threads are waiting for a signal

    for (int i = 0; i < NUM_ITERATIONS; i++) {
        int r = random() % 6;
        switch (r) {
        case 0:
            signal_count[TOBACCO]++;
            VERBOSE_PRINT("match available\n");
            uthread_cond_signal(a->match);
            VERBOSE_PRINT("paper available\n");
            uthread_cond_signal(a->paper);
            break;
        case 1:
            signal_count[PAPER]++;
            VERBOSE_PRINT("match available\n");
            uthread_cond_signal(a->match);
            VERBOSE_PRINT("tobacco available\n");
            uthread_cond_signal(a->tobacco);
            break;
        case 2:
            signal_count[MATCH]++;
            VERBOSE_PRINT("paper available\n");
            uthread_cond_signal(a->paper);
            VERBOSE_PRINT("tobacco available\n");
            uthread_cond_signal(a->tobacco);
            break;
        case 3:
            signal_count[TOBACCO]++;
            VERBOSE_PRINT("paper available\n");
            uthread_cond_signal(a->paper);
            VERBOSE_PRINT("match available\n");
            uthread_cond_signal(a->match);
            break;
        case 4:
            signal_count[PAPER]++;
            VERBOSE_PRINT("tobacco available\n");
            uthread_cond_signal(a->tobacco);
            VERBOSE_PRINT("match available\n");
            uthread_cond_signal(a->match);
            break;
        case 5:
            signal_count[MATCH]++;
            VERBOSE_PRINT("tobacco available\n");
            uthread_cond_signal(a->tobacco);
            VERBOSE_PRINT("paper available\n");
            uthread_cond_signal(a->paper);
            break;
        }
        VERBOSE_PRINT("agent is waiting for smoker to smoke\n");
        uthread_cond_wait(a->smoke);
    }
    uthread_mutex_unlock(a->mutex);
    return NULL;
}
int main(int argc, char **argv) {
  uthread_init(7);
  struct Agent *a = createAgent();
  uthread_t agent_thread;
  
  // Create condition variables
  match_tobacco = uthread_cond_create(a->mutex);
  match_paper = uthread_cond_create(a->mutex);
  paper_tobacco = uthread_cond_create(a->mutex);
  
  // Create threads, one for each of the "listeners"
  uthread_create(tobacco_listener, a);
  uthread_create(paper_listener, a);
  uthread_create(match_listener, a);
  
  // Create threads, one for each of the actors
  uthread_create(tobacco_smoker, a);
  uthread_create(match_smoker, a);
  uthread_create(paper_smoker, a);
  
  agent_thread = uthread_create(agent, a);
  uthread_join(agent_thread, NULL);
      
  // Assertions
  assert(signal_count[MATCH] == smoke_count[MATCH]);
  assert(signal_count[PAPER] == smoke_count[PAPER]);
  assert(signal_count[TOBACCO] == smoke_count[TOBACCO]);
  assert(smoke_count[MATCH] + smoke_count[PAPER] + smoke_count[TOBACCO] == NUM_ITERATIONS);
      
  printf("Smoke counts: %d matches, %d paper, %d tobacco\n",
           smoke_count[MATCH], smoke_count[PAPER], smoke_count[TOBACCO]);
  return 0;
}