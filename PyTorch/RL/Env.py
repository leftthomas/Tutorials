"""
An agent "o" is on the left of a 1 dimensional world, the treasure is on the rightmost location.

"""

import time

N_STATES = 6  # the length of the 1 dimensional world
ACTIONS = ['left', 'right']  # available actions
FRESH_TIME = 0.3  # fresh time for one move


def get_env_feedback(s, a):
    # this is how agent will interact with the environment
    if a == 'right':  # move right
        if s == N_STATES - 2:  # terminate
            s_ = 'terminal'
            r = 1
        else:
            s_ = s + 1
            r = 0
    else:  # move left
        r = 0
        if s == 0:
            s_ = s  # reach the wall
        else:
            s_ = s - 1
    return s_, r


def update_env(s, episode, step_counter):
    # this is how environment be updated
    env_list = ['-'] * (N_STATES - 1) + ['T']  # '------T' our environment
    if s == 'terminal':
        interaction = 'Episode %s: total_steps = %s' % (episode + 1, step_counter)
        print('\r{}'.format(interaction), end='')
        time.sleep(2)
        print('\r                                ', end='')
    else:
        env_list[s] = 'o'
        interaction = ''.join(env_list)
        print('\r{}'.format(interaction), end='')
        time.sleep(FRESH_TIME)
