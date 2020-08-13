
//using namespace std;

#include <iostream>

#include <cstdlib>
#include <ctime>
#include <iterator>
#include <vector>
#include <string>
#include <tuple>
#include <math.h>

typedef std::tuple
		< int, double, bool >
		computational_state;

typedef std::vector
		<  std::tuple < int, double, bool >  >
		generic_state;

typedef std::vector
		< std::tuple < int, double, int > >
		quantum_gate;

typedef std::tuple < int, double, int >
		gate_entry;

class Measurement
{

public:

	Measurement();

	Measurement
		(generic_state);

	int measure();

private:

	std::vector< double > prob_list;

};

class Grover
{
public:
	double search(int, int);

	Grover();
	Grover(int, int);

	void grover_print();

	int size();

private:
	int number_bits;
	int search_target;

	quantum_gate processor;

	void manufacture_grover();
};

Grover::Grover
()
{
	number_bits = 0;
	search_target = 0;

	manufacture_grover();
}

Grover::Grover
(int input_num_bits , int input_search_target)
{
	number_bits = input_num_bits;
	search_target = input_search_target;

	manufacture_grover();
}

void print
( generic_state input )
{
	int    number0 = 0;
	double number1 = 0;
	bool   bool0   = true;

	for
	    (
	        int i = 0;
			i < input.size();
			i++
		)
		{
			number0 = std::get<0> ( input.at ( i ) );
			number1 = std::get<1> ( input.at ( i ) );
			bool0   = std::get<2> ( input.at ( i ) );

			std::cout
				<< "("
				<< number0
				<< ","
				<< number1
				<< ","
				<< pow(-1, bool0)
				<< ")"
				<< std::endl;
		}

	return;
}

void print(gate_entry input)
{
	std::cout
		<< "("
		<< std::get <0> ( input )
		<< ","
		<< std::get <1> ( input )
		<< ","
		<< std::get <2> ( input )
		<< ")"
		<< std::endl;

	return;
}

void Grover::grover_print()
{
	quantum_gate input = processor;
	int num_elements = input.size();

	for (int it = 0; it < num_elements; it ++)
	{
		print( input.at( it ) );
	}

	return;
}

Measurement::Measurement()
{
	std::srand
	(	std::time( nullptr )	);
	// seed Measurement()
}

Measurement::Measurement
	(generic_state input)
{
	for
	(
		int it = 0;
			it < input.size();
			it ++
	)
	{
		computational_state temp_com;

		temp_com = input.at(it);

		prob_list.push_back
			(  std::get <1> ( temp_com )  );

	}

	std::srand
	(	std::time( nullptr )	);
	// seed Measurement()
}

int Measurement::measure()
{

		int random_number;
		int outcome;

		int net, bias[ prob_list.size() ];

		net = 0;



		for
		(
			int it = 0;
				it < prob_list.size();
				it ++
		)
		{
			bias[ it ] = 1000 * prob_list.at(it);
			net = bias[it] + net;
		}


		random_number = 1 + (	rand() % net	);
		// 1 to net


		if( random_number <= bias[0] )
		{
			outcome = 0;
		}

		else if( random_number <= bias[0] + bias[1] )
		{
			outcome = 1;
		}

		else if( random_number <= bias[0] + bias[1] + bias[2] )
		{
			outcome = 2;
		}

		else if( random_number <= bias[0] + bias[1] + bias[2] + bias[3] )
		{
			outcome = 3;
		}

		else if
		(
			random_number <=
				bias[0] + bias[1] + bias[2] + bias[3] + bias[4]
		)
		{
			outcome = 4;
		}
		else if
		(
				random_number <=
				bias[0] + bias[1] + bias[2]
				+ bias[3] + bias[4] + bias[5]
		)
		{
			outcome = 5;
		}

		else if
		(
				random_number <=
				bias[0] + bias[1] + bias[2]
				+ bias[3] + bias[4] + bias[5] + bias[6]
		)
		{
			outcome = 6;
		}

		else if
		(
			random_number <=
			bias[0] + bias[1] + bias[2]
			+ bias[3] + bias[4] + bias[5] + bias[6] + bias[7]
		)
		{
			outcome = 7;
		}

		return outcome;

}

std::string decToBinary(int input_dec)
{
	div_t divresult;

	std::string binaryNum, binaryNum1;

	binaryNum.reserve( 3 );

	int i = 0;
	int quotient = input_dec;

    for (int counter = 0; counter < 3; counter ++)
    {
    	if (quotient > 0)
    	{
        	divresult = div( quotient , 2);
        	quotient = divresult.quot;

        	binaryNum =
        			binaryNum
					+
        			std::to_string
					( divresult.rem );
    	}

    	else
    	{
    		binaryNum
				=
    			binaryNum +
				std::to_string( 0 );
    	}
    }

    std::reverse( binaryNum.begin(), binaryNum.end() );

    return binaryNum;
}

int bit_string_product(int dec0, int dec1)
{
	std::string bitstr0, bitstr1;
	int decimal0, decimal1;

	bitstr0 = decToBinary( dec0 );
	bitstr1 = decToBinary( dec1 );

	decimal0 = std::stoi( bitstr0 );
	decimal1 = std::stoi( bitstr1 );

	bool tempbool = 0;

	int bitset_counter = 0;

	for( int it = 0; it < bitstr0.size(); it++ )
	{
		tempbool =     ( bitstr0[ it ]-'0') & (bitstr1[ it ]-'0')  ;

		bitset_counter  =  bitset_counter + tempbool;
	}

	return bitset_counter;
}

/**
	hadamard accepts two arguments
	std::tuple < int, double, bool > input_states &&
	and integer number_of_bits,
	stimulate the effects of Hadamard gate,
	and returns
	std::vector <  std::tuple < int, double, bool >  >
	output_states
 */
generic_state hadamard
(
	computational_state input_state,
	int bits
)
{
	generic_state output;

	output.reserve(  pow( 2, bits )  );

	int indicator = std::get <0> ( input_state );

	for
	(
		int counter = 0;
		counter < pow( 2, bits );
		counter++
	)
	{


		output.push_back
		(
			std::make_tuple
			(
				counter,
				pow( pow(2, bits) , -1),
				bit_string_product( counter,  indicator) %2
			)
		);
	}

	return output;
}

bool sign(double input)
{
	return signbit(input);
}

void Grover::manufacture_grover
()
{
	quantum_gate grover;

	int N = pow( 2, number_bits );

	int max_entries = pow( N, 2 );

	double A, B;

	A = 2 * pow(N, -1) - 1;
	B = 2 * sqrt( N - 1 ) * pow( N, -1 );


	for
	(
			int row = 0;
				row < N;
				row ++
	)
	{

		for
		(
			int column = 0;
				column < N;
				column ++
		)
		{
			double entry_value;

			bool NotAssigned = false;

			if (row == search_target)
			{
				if(column == search_target)
				{
					entry_value = - A;

					NotAssigned++;
				}

				else if (column != search_target)
				{
					entry_value =
					   B *
					   pow( sqrt( N - 1 ), -1 );

					NotAssigned++;
				}
			}

			else if (row != search_target)
			{
				if(column == search_target)
				{
					entry_value =
						-1 * B *
						pow( sqrt( N - 1 ), -1 );

					NotAssigned++;
				}

				else if (column != search_target)
				{
					entry_value =
					   -1 * A *
					   pow( sqrt( N - 1 ), -1 )
						* pow( sqrt( N - 1 ), -1 );

					NotAssigned++;
				}
			}

			if( NotAssigned == false )
			{
				std::cout
					<< " entry not assigned. exit! "
					<< std::endl;

				break;
			}

			grover.push_back
			(
				std::make_tuple
				( row, entry_value, column )
			);
		}
	}

	processor = grover;
}

int Grover::size()
{
	return pow(2, number_bits);
}

double Grover::search
(int target_row, int target_column)
{
	int dimension_processor = processor.size();

	double output = 666;

	for
	(
		int it = 0;
			it < dimension_processor;
			it ++
	)
	{
		gate_entry temp_en = processor.at( it );

		int temp_row, temp_column;

		temp_row = std::get <0> ( temp_en );
		temp_column = std::get <2> ( temp_en );

		if
		(
			temp_row == target_row
			&&
			temp_column == target_column
		)
		{
			output = std::get <1> ( temp_en );
		}
	}

	return output;
}

generic_state oracle
(
	generic_state input_state
)
{
	generic_state output_state;

	int target_state, gate_dimension, num_bits;

	gate_dimension = input_state.size();

	num_bits = log2( gate_dimension );

	target_state = 5;
	num_bits = 3;

	if ( input_state.size() != pow(2,num_bits) )
	{
		std::cout
			<< "dimension not matching (oracle size 8 x 8)~"
			<< std::endl;
	}

	Grover oracle_grover
		= Grover ( num_bits, target_state );

		bool   output_sign;

		for
		(
			int row = 0;
				row < gate_dimension;
				row ++
		)
		{
			double output_value = 0;

			for
			(
					int col = 0;
						col < gate_dimension;
						col ++
			)
			{


				output_value =
					output_value
					+
					(
						oracle_grover.search
									  (row, col)
						*
						pow
						(
							-1,
							std::get <2>
							(
								input_state.at
								( col )
							)
						)
						*
						sqrt
						(
								std::get <1>
								(
									input_state.at
									( col )
								)
						)
					);
			}


			output_state.push_back
			(
				std::make_tuple
				(
						row,
						pow( output_value, 2 ),
						sign( output_value )
				)
			);
		}


	return output_state;
}

int main()
{
	// part.b. testing Measurement with psi_1, psi_2, pis_3

	generic_state psi_1, psi_2, psi_3;

	psi_1.push_back( std::make_tuple(0,0.5,false) );
	psi_1.push_back( std::make_tuple(7,0.5,false) );

	psi_2 = hadamard( std::make_tuple(0,0,false), 3 );

	psi_3.push_back( std::make_tuple(5,0.5,false) );

	Measurement ms_psi1, ms_psi2, ms_psi3;

	ms_psi1 = Measurement(psi_1);

	int count0 = 0, count7 = 0;
	for
	(
		int it = 0;
			it < 100;
			it ++
	)
	{
		int temp_out = ms_psi1.measure();

		if( temp_out == 0)
		{
			count0++;
		}

		if( temp_out == 1)
		{
			count7++;
		}
	}

	std::cout << "[psi1] count0 " << count0
			  << " count7 " << count7
			  << std::endl;

	//
	ms_psi2 = Measurement(psi_2);

		int count[8] = {0,0,0,0,0,0,0,0};
		for
		(
			int it = 0;
				it < 800;
				it ++
		)
		{
			int temp_out = ms_psi2.measure();

			if( temp_out == 0)
			{
				count[0] ++;
			}

			else if( temp_out == 1)
			{
				count[1]++;
			}

			else if( temp_out == 2)
			{
				count[2]++;
			}

			else if( temp_out == 3)
			{
				count[3]++;
			}

			else if( temp_out == 4)
			{
				count[4]++;
			}
			else if( temp_out == 5)
			{
				count[5]++;
			}

			else if( temp_out == 6)
			{
				count[6]++;
			}

			else if( temp_out == 7)
			{
				count[7]++;
			}
		}

		std::cout << "[psi2] count0 " << count[0]
				  << " count1 " << count[1]
				  << " count2 " << count[2]
				  << " count3 " << count[3]
				  << " count4 " << count[4]
				  << " count5 " << count[5]
				  << " count6 " << count[6]
				  << " count7 " << count[7]
				  << std::endl;

	//
		ms_psi3 = Measurement(psi_3);

		int count_5 = 0;
		for
		(
			int it = 0;
				it < 100;
				it ++
		)
		{
			int temp_out = ms_psi1.measure();

			if( temp_out == 0)
			{
				count0++;
			}

			count_5++;
		}

		std::cout << "[psi3] count_5 "
				  << count_5
				  << std::endl;

	// part.c. testing Grover_Interations && Measurement
	int num_iterations = 1;

	computational_state com_st (0,0,0);
	generic_state input,output;

	input = hadamard( com_st, 3 );

	output = oracle( input );

	for (int it = 0; it < num_iterations - 1 ; it++)
	{
		output = oracle( output );
	}

	Measurement main_ms( output );

	int index, num_trials;

	index = 0;
	num_trials = 1000;

	for
	(
		int repeats = 0;
			repeats < num_trials;
			repeats++
	)
	{
		int temp_outcome;

		temp_outcome = main_ms.measure();

		if
		(
			temp_outcome == 5
		)
		{
			index++;
		}
	}

	std::cout << "IF k = " << num_iterations
			<< " OUT OF " << num_trials << " TRIALS, "
			<< index << " TIMES W/ OUTCOME == 5."
			<< std::endl;










	return 0;
}














