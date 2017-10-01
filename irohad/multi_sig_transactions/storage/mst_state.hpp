/**
 * Copyright Soramitsu Co., Ltd. 2017 All Rights Reserved.
 * http://soramitsu.co.jp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef IROHA_MST_STATE_HPP
#define IROHA_MST_STATE_HPP

#include <unordered_set>
#include <memory>
#include <vector>
#include "logger/logger.hpp"
#include "model/transaction.hpp"

namespace iroha {

  class MstState {
   public:
// -------------------------------| public api |--------------------------------

    using DataType = std::shared_ptr<iroha::model::Transaction>;

    MstState();

    /**
     * Add transaction to current state
     * @param rhs - transaction for insertion
     * @return this
     */
    MstState &operator+=(const DataType &rhs);

    /**
     * Concat internal data of states
     * @param rhs - object for joining
     * @return State is union of this and right states
     */
    MstState operator+(const MstState &rhs) const;

    /**
     * Operator provide difference between this and rhs operator
     * @param rhs, state for removing
     * @return State that provide difference between left and right states
     * axiom operators:
     * A + B == B + A
     * A - B == A + (B - A)
     */
    MstState operator-(const MstState &rhs) const;

    /**
     * Provide transactions, that contains in state
     */
    std::vector<DataType> getTransactions() const;

   private:
// -----------------------------| private classes |-----------------------------

    /**
     * Hash calculation for transaction
     */
    class ShpTxHasher {
     public:

      ShpTxHasher() {
        log_ = logger::log("TxHasher");
      }

      size_t operator()(const DataType &tx) const {
        auto hash = string_hasher(tx.get()->tx_hash.to_string());
        return hash;
      }

     private:
      std::hash<std::string> string_hasher;
      logger::Logger log_;
    };

    /**
     * Dereference for equality of wrapped objects
     */
    template<typename T>
    class DereferenceEquals {
     public:
      DereferenceEquals() {
        log_ = logger::log("DereferenceEquals");
      }

      bool operator()(const T &lhs, const T &rhs) const {
        return (*lhs) == (*rhs);
      }

     private:
      logger::Logger log_;
    };

// -------------------------------| private api |-------------------------------

    using InternalStateType = std::unordered_set<DataType,
                                                 ShpTxHasher,
                                                 DereferenceEquals<DataType>>;

    MstState(InternalStateType transactions);
// ---------------------------------| fields |----------------------------------

    InternalStateType internal_state_;
    logger::Logger log_;
  };

} // namespace iroha
#endif //IROHA_MST_STATE_HPP