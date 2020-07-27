#!/home/hugens/devel/env/bin/python3

import numpy as np
import numpy.random as nr

class walker:
    def __init__(self, alpha, lamb, gamma):
        # fixed
        self.alpha = alpha
        self.lamb  = lamb
        self.gamma = gamma
        self.moves = np.array([ [0, -1], [1, 0], [-1, 0], [0, 1] ])

        # initial
        self.q = nr.random([7, 10, 4])
        self.allsteps = np.zeros(2000)

    def evaluate_policy(self):
        mapp = np.zeros([7, 10])
        seq  = []
        histo  = {}

        self.pos = np.array([3, 0], dtype = int)
        self.act = 3

        mapp[self.pos[0], self.pos[1]] += 1
        seq.append(list(self.pos))

        while not self.terminated():
            self.take_action()
            self.environment_action()

            mapp[self.newpos[0], self.newpos[1]] += 1
            seq.append(list(self.newpos))

            self.choose_action()
            self.pos = np.copy(self.newpos)
            self.act = np.copy(self.newact)

        for steps in self.allsteps:
            histo[steps] = histo.get(steps, 0) + 1

        print('Last epsilon: ', self.epsi, '\n')
        print('Sequence of states: \n', seq, '\n')
        print('Trajectory: \n', mapp, '\n')
        print('Steps histogram:')
        print('steps : no. of episodes with those steps \n')

        for key in sorted(histo):
            print('{} : {}'.format(int(key), histo[key]))

    def is_inside(self):
        # wall behaviour, checks if bot escaped and puts it inside

        if (self.newpos[0] < 0) or (self.newpos[0] > 6):
            self.newpos = np.copy(self.pos)
        elif (self.newpos[1] < 0) or (self.newpos[1] > 9):
            self.newpos = np.copy(self.pos)

    def terminated(self):
        # checks if current position is target position

        if (self.pos[0] == 3) and (self.pos[1] == 7):
            return True
        else:
            return False

    def take_action(self):
        # takes the step, i.e., updates new position

        self.newpos = self.pos + self.moves[self.act]
        self.is_inside()

    def choose_action(self):
        # policy funcion, it acts greedly with probability 1-epsi 
        # and randomly with probability epsi

        if nr.rand() > self.epsi:
            self.newact = np.argmax(self.q[self.newpos[0], self.newpos[1], :])
        else:
            self.newact = nr.randint(4)

    def delta(self):
        # calculates TD-error delta

        newq = -1 + self.gamma * self.q[ self.newpos[0], self.newpos[1], self.newact ]
        oldq = self.q[ self.pos[0], self.pos[1], self.act ]
        return newq - oldq

    def environment_action(self):
        if (self.newpos[1] > 2):
            if (self.newpos[1] <= 5):
                self.newpos[0] -= 1
            elif (self.newpos[1] <= 7):
                self.newpos[0] -= 2
            elif (self.newpos[1] == 8):
                self.newpos[0] -= 1
        if self.newpos[0] < 0:
            self.newpos[0] = 0

    def run(self):
        # main function, iterates through episodes

        for e in range(len(self.allsteps)):
            self.epsi = 1/(e+1)**2
            #print('epsilon = ', self.epsi)
            self.begin_episode()
            self.allsteps[e] = self.steps

            #print('steps :', self.steps, end = '\r')

        self.evaluate_policy()

    def begin_episode(self):
        # secondary function, iterates through time-steps

        self.steps = 0
        self.elig  = np.zeros([7, 10, 4])
        self.pos   = np.array([3, 0], dtype = int)
        self.act   = np.argmax(self.q[self.pos[0], self.pos[1], :])

        while not self.terminated():
            self.steps += 1
            self.time_step()
            # print('pos   :', self.pos, end='\r', flush = True)

    def time_step(self):
        self.elig[self.pos[0], self.pos[1], self.act] += 1

        self.take_action()
        self.environment_action()
        self.choose_action()

        self.q    = self.q + self.alpha * self.delta() * self.elig
        self.elig = self.gamma * self.lamb * self.elig
        self.pos  = np.copy(self.newpos)
        self.act  = np.copy(self.newact)

bot = walker(1, 0.9, 0.4)
bot.run()
