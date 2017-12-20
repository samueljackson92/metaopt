import unittest
import pyoptima as opt


class SwarmTest(unittest.TestCase):

    def test_with_parabola(self):
        """ Test with a simple parabolic function with 2 variables """
        hyper_params = {'phi_local': 1, 'phi_global': 1, 'omega': 0.01}
        params = {'x0': (-1, 1), 'x1': (-1, 1)}
        num_particles = 2

        s = opt.Swarm(params, hyper_params, num_particles)
        s.optimize(opt.parabola, 100)

        # bst_solution = s.getBestSolution()

        # for value in bst_solution:
        #     self.assertAlmostEqual(value, 0)

    # def test_with_ackley(self):
    #     """ Test with the ackley function with 2 variables """
    #     hyper_params = {'phi_local': 0.1, 'phi_global': 0.1, 'omega': 0.1}
    #     params = {'x0': (-40, 40), 'x1': (-40, 40)}
    #     num_particles = 10

    #     s = opt.Swarm(params, hyper_params, num_particles)
    #     s.optimize(opt.ackley, 1000)

    #     bst_solution = s.getBestSolution()

    #     for value in bst_solution:
    #         self.assertAlmostEqual(value, 1)

    # def test_python_function(self):
    #     """ Test with a function defined on the python side and passed
    #     to the c++ layer. This is equivilent to the parabola test above
    #     """

    #     def parabolic(params):
    #         x0, x1 = params['x0'], params['x1']
    #         return x0**2 + x1**2

    #     hyper_params = {'phi_local': 1, 'phi_global': 1, 'omega': 0.01}
    #     params = {'x0': (-1, 1), 'x1': (-1, 1)}
    #     num_particles = 10

    #     s = opt.Swarm(params, hyper_params, num_particles)
    #     s.optimize(parabolic, 100)

    #     bst_solution = s.getBestSolution()

    #     for value in bst_solution:
    #         self.assertAlmostEqual(value, 0)


if __name__ == "__main__":
    unittest.main()
