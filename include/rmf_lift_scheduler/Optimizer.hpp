#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "Database.hpp"

namespace rmf{
namespace scheduler{

	/// \brief Class to get the priority ranking of lift states
	/// \tparam Heuristic Heuristic function to calculate the relative importance of a lift state
	/// \tparam State_Type State type to perform calculation on
	template <typename Heuristic, typename State_Type>
	class Optimizer{
	public:
		using Result = std::pair<std::string, float>;

		struct Standard_Compare
		{
			bool operator()(const Result& lhs, const Result& rhs) const
			{
				return lhs.second < rhs.second;
			}
		};

		/// \brief Get the priority ranking of lift states
		/// \param ranking_output Vector to populate the priority rankings
		/// \param states Vector of states
		/// \tparam Compare_Func Comparator callable object to sort the ranking_output
		template<typename Compare_Func = Standard_Compare>
		void rank(std::vector<Result>& ranking_output, 
			std::vector<State_Type>& states)
		{
			ranking_output.clear();
			for(auto it = states.begin(); it != states.end(); ++it)
			{
				ranking_output.push_back(
					std::make_pair(it->rmf_lift_state.lift_name, heuristic(*it))
				);
			}
			std::sort(ranking_output.begin(), ranking_output.end(), Compare_Func());
		}

	private:
		Heuristic heuristic;
	};

}
}