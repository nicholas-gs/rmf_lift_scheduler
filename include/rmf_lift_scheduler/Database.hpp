#pragma once

#include <unordered_set>
#include <exception>
#include <memory>

#include "State.hpp"

namespace rmf {
namespace scheduler {

/// \brief Database to keep track of all the lift cabins.
///        Internally, an unordered_set is used as the underlying storage.
/// \tparam State_Type Element to be stored
/// \tparam Hash_Type Hashing function for State_Type
/// \tparam Equal_Type Comparator between two State_Type elements
template<typename State_Type, typename Hash_Type, typename Equal_Type>
class Database
{
public:
  using Impl_Val_Type = State_Type;
  using Impl_DB_Type = std::unordered_set<Impl_Val_Type, Hash_Type, Equal_Type>;
  using unique_ptr = std::unique_ptr<Database>;

  /// \brief Construct a database object by populating it
  /// \tparam InputIterator
  /// \param first
  /// \param last
  /// \return std::unique_ptr of a database instance
  template<typename InputIterator>
  static unique_ptr
  make(InputIterator first, InputIterator last);

  /// \brief Get all the states in the database
  /// \param container A vector to store the states in
  void all(std::vector<Impl_Val_Type>& container) const
  {
    container.clear();
    container.reserve(internal_db.size());
    for (auto it = internal_db.cbegin(); it != internal_db.end(); ++it)
    {
      container.push_back(*it);
    }
  }

  /// \brief Get a reference to a lift state. Matching is done using Equal_Type
  /// \param val Element of type Impl_Val_Type that is used to find lift state
  /// \return Reference to the state of the specified lift
  /// \throws std::runtime_error if specified lift name cannot be found
  Impl_Val_Type& find(const Impl_Val_Type& val)
  {
    auto result = internal_db.find(val);
    if (result != internal_db.end())
    {
      return *result;
    }
    throw std::runtime_error("Lift not found");
  }

  /// \brief Update the state of a lift.
  /// \param state New state to update
  void update(const Impl_Val_Type& state)
  {
    Impl_Val_Type& ref = find(state);
    ref.update(state);
  }

  /// \brief Remove a lift. Matching is done using Equal_Type
  /// \param lift Lift to remove
  /// \return true if removed
  bool remove_lift(const Impl_Val_Type& lift)
  {
    return internal_db.erase(lift) == 1;
  }

  /// \brief Insert a lift into the database.
  /// \param lift Lift to insert
  void insert_lift(const Impl_Val_Type& lift)
  {
    internal_db.insert(lift);
  }

private:
  // Keep track of the state of all the lift cabins
  Impl_DB_Type internal_db;

  /// \brief Private constructor. Use the static make(...) function
  ///        to construct an instance of the database class.
  template<typename InputIterator>
  Database(InputIterator first, InputIterator last)
  : internal_db(first, last)
  {}
};

template<typename State_Type, typename Hash_Type, typename Equal_Type>
template<typename InputIterator>
std::unique_ptr<Database<State_Type, Hash_Type, Equal_Type>>
Database<State_Type, Hash_Type, Equal_Type>::make(InputIterator first,
  InputIterator last)
{
  std::unique_ptr<Database<State_Type, Hash_Type, Equal_Type>> db_ptr(
    new Database(first, last)
  );
  return db_ptr;
}

}
}