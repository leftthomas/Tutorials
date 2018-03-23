"""
A simple example for Reinforcement Learning using table lookup Sarsa method.

"""

from RL import Env
from RL import Tools

ALPHA = 0.1  # learning rate
GAMMA = 0.9  # discount factor
MAX_EPISODES = 13  # maximum episodes


def sarsa():
    # main part of Sarsa loop
    q_table = Tools.build_q_table(Env.N_STATES, Env.ACTIONS)
    for episode in range(MAX_EPISODES):
        step_counter = 0
        s = 0
        is_terminated = False
        Env.update_env(s, episode, step_counter)
        a = Tools.choose_action(s, q_table)

        while not is_terminated:

            s_, r = Env.get_env_feedback(s, a)  # take action & get next state and reward
            q_predict = q_table.ix[s, a]
            if s_ != 'terminal':
                a_ = Tools.choose_action(s_, q_table)
                q_target = r + GAMMA * q_table.ix[s_, a_]  # next state is not terminal
            else:
                q_target = r  # next state is terminal
                is_terminated = True  # terminate this episode
                a_ = None

            q_table.ix[s, a] += ALPHA * (q_target - q_predict)  # update
            s = s_  # move to next state
            a = a_
            Env.update_env(s, episode, step_counter + 1)
            step_counter += 1
            # print(q_table)
    return q_table


if __name__ == "__main__":
    q_table = sarsa()
    print('\nQ-table:')
    print(q_table)
