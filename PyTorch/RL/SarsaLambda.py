"""
A simple example for Reinforcement Learning using table lookup Sarsa(lambda) method.

"""

from PyTorch.RL import Env
from PyTorch.RL import Tools

LAMBDA = 0.9  # lambda factor
ALPHA = 0.1  # learning rate
GAMMA = 0.9  # discount factor
MAX_EPISODES = 13  # maximum episodes


def sarsa_lambda():
    # main part of Sarsa(lambda) loop
    q_table = Tools.build_q_table(Env.N_STATES, Env.ACTIONS)
    eligibility_trace = q_table.copy()
    for episode in range(MAX_EPISODES):
        step_counter = 0
        s = 0
        eligibility_trace *= 0
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

            eligibility_trace.ix[s, a] += 1
            # print(eligibility_trace)
            # update
            q_table += ALPHA * (q_target - q_predict) * eligibility_trace
            # decay eligibility trace after update
            eligibility_trace *= GAMMA * LAMBDA

            s = s_  # move to next state
            a = a_
            Env.update_env(s, episode, step_counter + 1)
            step_counter += 1
            # print(q_table)
    return q_table


if __name__ == "__main__":
    q_table = sarsa_lambda()
    print('\nQ-table:')
    print(q_table)
