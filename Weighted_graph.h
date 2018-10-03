/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>

// include whatever classes you want

class Weighted_graph {
	private:
		// your implementation here
		//  you can add both private member variables and private member functions
		double **matrix;
		int vertice_num;
		int *vertice_degree;
		double *distance_array;
		int *visited;
		
		int edge_num;
		static const double INF;

	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();
		
		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double distance( int, int );

		void insert( int, int, double );

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

// Your implementation here


Weighted_graph::Weighted_graph(int m){
	if (m<=0){
		m=1;
	}
	
	matrix = new double*[m];
	vertice_degree = new int[m];
	
	for (int i=0; i<m; i++){
		vertice_degree[i] = 0;
	}
	
	visited = new int[m];
	for (int i=0; i<m; i++){
		visited[i] = 0;
	}
	
	distance_array = new double[m];
	for (int i=0; i<m; i++){
		distance_array[i] = 0;
	}
	
	for (int i=0; i<m; i++){
		matrix[i] = new double[m];
	}
	
	for (int i=0; i<m; i++){
		for (int j=0; j<m; j++){
			matrix[i][j] = INF;
		}
		matrix[i][i] = 0;
	}
	
	vertice_num = m;
	edge_num =0;
}

Weighted_graph::~Weighted_graph(){
	
	for (int i=0; i<vertice_num; i++){
		delete[] matrix[i];
	}
	
	delete[] matrix;
	delete[] vertice_degree;
	delete[] visited;
	delete[] distance_array;
	
	
	
	
}


//accessors---------------------------------------------------------------------------

int Weighted_graph::degree( int n ) const{
	
	//s
	if (n>= vertice_num){
		throw illegal_argument();
	}
	
	else if (n<0){
		throw illegal_argument();
	}
	
	else{
		return vertice_degree[n];
	}
}

int Weighted_graph::edge_count() const{
	return edge_num;
	
}

double Weighted_graph::adjacent( int m, int n ) const{
	if (m >= vertice_num || n >= vertice_num || m<0 || n<0){
		throw illegal_argument();
	}
	
	if (m==n){
		return 0;
	}
	
	return matrix[m][n];
	
	
	
	
}


//Mutators-----------------------------------------------------------------------




void Weighted_graph::insert( int m, int n, double w ){
	if (w <= 0 || w==INF){
		throw illegal_argument();
	}
	if (m >= vertice_num || n >= vertice_num || m<0 || n<0){
		throw illegal_argument();
	}
	if (m==n){
		throw illegal_argument();
	}
	
	if (matrix[m][n] == INF){
		matrix[m][n] = w;
		matrix[n][m] = w;
		edge_num++;
		vertice_degree[n]++;
		vertice_degree[m]++;
	}
	else if (matrix[m][n] != INF){
		matrix[m][n] = w;
		matrix[n][m] = w;
	}
	
	
}




double Weighted_graph::distance( int m, int n ){
	if (m >= vertice_num || n >= vertice_num || m<0 || n<0){
		throw illegal_argument();
	}
	
	
	
	if (m==n){
		return 0;
	}
	
	for (int i=0; i<vertice_num; i++){
		distance_array[i] = INF;
	}
	for (int i=0; i<vertice_num; i++){
		visited[i] =0;
	}
	
	int visited_all = 0;
	visited[m] =1;
	distance_array[m] = 0;
	
	int index = m;
	
	while(visited_all ==0){
		
		for (int i=0; i<vertice_num;i++){
			
			if (matrix[index][i] != INF && matrix[index][i] + distance_array[index] < distance_array[i] && matrix[index][i]!=0){
	
				distance_array[i] = matrix[index][i] + distance_array[index];
				
			}
			
		}
		
		visited[index] =1;
		
		double min_distance = INF;
		
		for(int i = 0; i < vertice_num; i++)
		{
			if(distance_array[i] <= min_distance && visited[i] == 0)
			{
				
				min_distance = distance_array[i];
				index = i;
			}
		}
		
		visited_all =1;
		
		for (int i=0; i<vertice_num; i++){
			if (visited[i] ==0){
				visited_all =0;
			}
		}
		
		
		
		
		
		
		
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
 	
	
	return distance_array[n];
	
	
	
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif