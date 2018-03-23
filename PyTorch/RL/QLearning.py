"""
A simple example for Reinforcement Learning using table lookup Q-learning method.

"""
from RL import Env
from RL import Tools

ALPHA = 0.1  # learning rate
GAMMA = 0.9  # discount factor
MAX_EPISODES = 13  # maximum episodes


def q_learning():
    # main part of Q learning loop
    q_table = Tools.build_q_table(Env.N_STATES, Env.ACTIONS)
    for episode in range(MAX_EPISODES):
        step_counter = 0
        s = 0
        is_terminated = False
        Env.update_env(s, episode, step_counter)
        while not is_terminated:

            a = Tools.choose_action(s, q_table)
            s_, r = Env.get_env_feedback(s, a)  # take action & get next state and reward
            q_predict = q_table.ix[s, a]
            if s_ != 'terminal':
                q_target = r + GAMMA * q_table.iloc[s_, :].max()  # next state is not terminal
            else:
                q_target = r  # next state is terminal
                is_terminated = True  # terminate this episode

            q_table.ix[s, a] += ALPHA * (q_target - q_predict)  # update
            s = s_  # move to next state

            Env.update_env(s, episode, step_counter + 1)
            step_counter += 1
            # print(q_table)
    return q_table


if __name__ == "__main__":
    q_table = q_learning()
    print('\nQ-table:')
    print(q_table)
