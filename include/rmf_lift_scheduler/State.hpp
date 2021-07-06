#pragma once

#include <string>

#include "rmf_lift_msgs/msg/lift_state.hpp"

namespace rmf {
namespace scheduler {

/// \brief Base class which represents the current state of a lift cabin.
///        This represents a wrapper around the standard rmf_lift_msgs
///        state with other useful fields for calculating cost.
///		   Inherit from this class to provide a custom implementation of 
///        the lift state.
///        The only other requirement is that there must be an update function
///        which takes in a const reference to the derived class object.
struct State_Base
{
  State_Base(
    const rmf_lift_msgs::msg::LiftState& lift_state
  )
  : rmf_lift_state(lift_state)
  {}

  rmf_lift_msgs::msg::LiftState rmf_lift_state;

  /// \brief Update the state using another state object
  /// \param other Reference state object to update to.
  void update(const rmf_lift_msgs::msg::LiftState& other)
  {
    // todo : remove unnecessary copying
    rmf_lift_state = other;
  }

};

}
}