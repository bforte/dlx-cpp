#include <boost/python.hpp>

#include <AlgorithmDLX.hpp>

#include <iostream>
#include <vector>

namespace py = boost::python;

/* Solution wrapper */
struct Solution {
	Solution(py::list& init_list) {
		/*
			This is the constructor for the wrapper, it expects
			input of the form unsigned[][] which will describe
			the boolean matrix for the exact-cover algorithm.
		*/

		this->m = (int) len(init_list);
		this->n = (int) len(py::extract<py::list>(init_list[0]));

		std::vector<std::vector<unsigned>> input_rows(m, std::vector<unsigned>(n));
		py::list in_row;

		// Loop over all rows
		for (int i = 0; i < this->m; ++i) {

			in_row = py::extract<py::list>(init_list[i]);

			// Check input for errors
			if (this->n != len(in_row)) {
				std::cerr << "Malformed input: Row #" << i
					<< " is of length " << len(in_row)
					<< ".. (exp: " << n << ")" << std::endl;
				exit(-1);
			}

			// Read each entry into input_rows
			for (int j = 0; j < this->n; ++j) {
				input_rows[i][j] = py::extract<unsigned>(in_row[j]);
			}
		}

		// Initialize an instance of ExactCoverProblem and solve it
		auto problem = ExactCoverProblem::dense(input_rows, 0);
		AlgorithmDLX dlx(problem);
		auto result = dlx.search();

		// Set number of solutions
		this->number_of_solutions = result.number_of_solutions;

		// Make the solutions accessible as a list
		for (auto v_solution : result.solutions) {
			py::list p_solution;
			for (auto e : v_solution) {
				p_solution.append(e);
			}
			this->solutions.append(p_solution);
		}

		// Make the profile accessible as a list
		for (auto e : result.profile) {
			this->profile.append(e);
		}
	}

	// Solution attributes
	int m,n;
	unsigned number_of_solutions;
	py::list solutions;
	py::list profile;
};


/* Boost-module description: */
BOOST_PYTHON_MODULE(libexactcover) {

	py::class_<Solution>("Solution", py::init<py::list&>())
		.def_readonly("number_of_solutions", &Solution::number_of_solutions)
		.def_readonly("solutions", &Solution::solutions)
		.def_readonly("profile", &Solution::profile)
		;
}
