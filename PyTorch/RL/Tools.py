import numpy as np
import pandas as pd

from PyTorch.RL import Env

# greedy police
EPSILON = 0.9


def build_q_table(n_states, actions):
    table = pd.DataFrame(
        # q_table initial values
        np.zeros((n_states, len(actions))),
        # actions's name
        columns=actions,
    )
    # show table
    # print(table)
    return table


def choose_action(state, q_table):
    # this is how to choose an action
    state_actions = q_table.iloc[state, :]
    # act non-greedy or state-action have no value
    if (np.random.uniform() > EPSILON) or (state_actions.all() == 0):
        action_name = np.random.choice(Env.ACTIONS)
    else:  # act greedy
        action_name = state_actions.idxmax()
    return action_name
