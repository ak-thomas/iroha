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

#ifndef IROHA_TEST_STORAGE_HPP
#define IROHA_TEST_STORAGE_HPP

#include "ametsuchi/storage.hpp"

namespace iroha {
  namespace ametsuchi {

    /**
     * Storage interface aimed for tests purposes;
     *
     */
    class TestStorage : public Storage {
     public:

      /**
       * Raw insertion of blocks without validation
       * @param block - block for insertion
       */
      virtual void insertBlock(model::Block block) = 0;

      /**
       * Remove all information from ledger
       */
      virtual void dropStorage() = 0;

      virtual ~TestStorage() = default;
    };

  }  // namespace ametsuchi
}  // namespace iroha
#endif //IROHA_TEST_STORAGE_HPP
