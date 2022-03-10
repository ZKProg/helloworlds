#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>
#include <chrono>
#include <omp.h>


using namespace std;

inline double computeFx(double x) {
	return (4.0 / (1 + x * x));
}

int main(int argc, char** argv) {

	system("color c");

	// Init
	double steps = 100000000;
	double definition = 1.0 / steps;
	double Pi = 0.0;
	bool sequential = false;
	int threads = 16;

	// Benchmark Start
	std::chrono::milliseconds start = std::chrono::duration_cast<chrono::milliseconds>(
		chrono::system_clock::now().time_since_epoch()
	);

	for (int rep = 0; rep < 5; rep++) {

		Pi = 0.0;

		if (sequential) {

			for (double s = 0; s < 1.0; s += definition) {
				Pi += computeFx(s) * definition;
			}

		}
		else {

			// Omp implementation
			omp_set_num_threads(threads);
			double* results = new double[steps];


			#pragma omp parallel
			{
				int thread = omp_get_thread_num();

				for (int i = 0; i < (int)steps / threads; i++) {

					int index = thread * ((int)steps / threads) + i;
					double independant = index * definition;

					results[index] = computeFx(independant) * definition;

				}

			}

			for (int i = 0; i < steps - 1; i++) Pi += results[i];
			delete results;
		}
	}

	// Benchmark Stop
	chrono::milliseconds end = chrono::duration_cast<chrono::milliseconds>(
		chrono::system_clock::now().time_since_epoch()
	);


	// Result
	if (Pi == 0)
		cout << "Pi has not been computed." << endl;
	else
		cout << setprecision(15) << "Pi equals: " << Pi << endl;
	finally:
		cout << "Computation terminated in " << end.count() - start.count() << "ms." << endl;

	return 0;
}
