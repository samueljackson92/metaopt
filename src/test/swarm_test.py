import unittest
import pyoptima as opt


class SwarmTest(unittest.TestCase):

    def test_swarm_with_parabola(self):
        hyper_params = {'phi_local': 1, 'phi_global': 1, 'omega': 0.01}
        params = {'x0': (-1, 1), 'x1': (-1, 1)}
        num_particles = 100

        s = opt.Swarm(params, hyper_params, num_particles)
        s.optimize(opt.parabola, 100)

        bst_solution = s.getBestSolution()

        for value in bst_solution:
            self.assertAlmostEqual(value, 0)

    def test_swarm_with_rosen(self):
        hyper_params = {'phi_local': 1, 'phi_global': 1, 'omega': 0.1}
        params = {'x0': (-1, 1), 'x1': (-1, 1)}
        num_particles = 100

        s = opt.Swarm(params, hyper_params, num_particles)
        s.optimize(opt.rosen, 1000)

        bst_solution = s.getBestSolution()

        for value in bst_solution:
            self.assertAlmostEqual(value, 1)

if __name__ == "__main__":
    unittest.main()
