# rmf_lift_scheduler

_Work in progress_

A framework for prioritizing lifts.

There are many different ways to calculate the priority of lift cabins. The optimization can be done to minimize wait time, travel time, or even electricity usage. This library is meant to allow for the user to dictate the heuristic for optimization.

## Classes

* State - Base class which acts as a wrapper for rmf_lift_msgs/LiftState objects. The intuition is extending this base class allows for other fields that can be used for calculating priority.
* Database - Storage for lift states. Implemented using a unordered_set as the underlying data storage container.
* Optimizer - Calculate the score for each lift depending on a user-defined heuristic and according to the lift's state.