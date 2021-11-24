#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "Tests/VectorAdditionTest/euclidean_vector2d.h"

int main(int argc, const char* argv[]) {
  // Get input
  std::cout << "`magnitude` units `angle_of_rotation` degrees `direction_of_angle_of_rotation` of `direction_of_axis`" << std::endl;

  std::string first_vector_input;
  std::cout << "Type the first vector using the above template. Do not include the back ticks." << std::endl << ">>> ";
  std::getline(std::cin, first_vector_input);

  std::string second_vector_input;
  std::cout << "Type the second vector using the above template. Do not include the back ticks." << std::endl << ">>> ";
  std::getline(std::cin, second_vector_input);

  // Parse input
  std::vector<std::string> first_vector_input_parsed;
  split(first_vector_input_parsed, first_vector_input, boost::is_any_of(" "));
  for (auto iterator = first_vector_input_parsed.begin(); iterator != first_vector_input_parsed.end();)
    if (*iterator == "units" || *iterator == "degrees" || *iterator == "of") iterator = first_vector_input_parsed.erase(iterator);
    else ++iterator;

  std::vector<std::string> second_vector_input_parsed;
  split(second_vector_input_parsed, second_vector_input, boost::is_any_of(" "));
  for (auto iterator = second_vector_input_parsed.begin(); iterator != second_vector_input_parsed.end();)
    if (*iterator == "units" || *iterator == "degrees" || *iterator == "of")
      iterator = second_vector_input_parsed.erase(iterator);
    else
      ++iterator;

  // Convert input into desired variables
  const float first_vector_magnitude = atof(first_vector_input_parsed[0].c_str());
  const float first_vector_rotation_angle = atof(first_vector_input_parsed[1].c_str());
  const euclidean_vector2d::directions first_vector_axis_direction = euclidean_vector2d::convert_string_to_directions(first_vector_input_parsed[3]);
  const euclidean_vector2d::directions first_vector_rotation_direction = euclidean_vector2d::convert_string_to_directions(first_vector_input_parsed[2]);

  const float second_vector_magnitude = atof(second_vector_input_parsed[0].c_str());
  const float second_vector_rotation_angle = atof(second_vector_input_parsed[1].c_str());
  const euclidean_vector2d::directions second_vector_axis_direction = euclidean_vector2d::convert_string_to_directions(second_vector_input_parsed[3]);
  const euclidean_vector2d::directions second_vector_rotation_direction = euclidean_vector2d::convert_string_to_directions(second_vector_input_parsed[2]);

  // Create `first_euclidean_vector` and `second_euclidean_vector` and add them
  const auto first_euclidean_vector = euclidean_vector2d(first_vector_magnitude, first_vector_rotation_angle, first_vector_axis_direction, first_vector_rotation_direction);
  const auto second_euclidean_vector = euclidean_vector2d(second_vector_magnitude, second_vector_rotation_angle, second_vector_axis_direction, second_vector_rotation_direction);
  const auto resultant_euclidean_vector = first_euclidean_vector + second_euclidean_vector;

  // Display the members of `resultant_euclidean_vector`
  std::cout << resultant_euclidean_vector.magnitude << " units " << resultant_euclidean_vector.rotation_angle << " degrees " << resultant_euclidean_vector.rotation_direction << " of " << resultant_euclidean_vector.axis_direction << std::endl;

  return 0;
}
