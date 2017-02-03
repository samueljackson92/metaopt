import unittest
import numpy as np
import pyoptima as opt


class SimulatedAnnealingTest(unittest.TestCase):

    def test_with_parabola(self):
        """ Test with a simple parabolic function with 2 variables """

        def neighbour_func(params):
            new_params = params
            params['x0'] += np.random.uniform(-1., 1.)
            params['x1'] += np.random.uniform(-1., 1.)
            return new_params

        hyper_params = {
            'temperature_func': lambda t, i: t/np.log(i+2),
            'neighbour_func': neighbour_func,
            'initial_temp': 100000.0
        }

        params = {}
        params["x0"] = np.random.uniform(-10., 10.)
        params["x1"] = np.random.uniform(-10., 10.)
        s = opt.SimulatedAnnealing(params, hyper_params)
        s.optimize(opt.parabola, 100000)

        bst_solution = s.get_best_parameters()

        for value in bst_solution.itervalues():
            self.assertAlmostEqual(value, 0, 2)

if __name__ == "__main__":
    unittest.main()
