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

#ifndef IROHA_PROTO_TRANSFER_ASSET_HPP
#define IROHA_PROTO_TRANSFER_ASSET_HPP

#include "interfaces/commands/transfer_asset.hpp"

namespace shared_model {
  namespace proto {

    class TransferAsset final : public interface::TransferAsset {
     private:
      using RefTransferAsset =
          detail::ReferenceHolder<iroha::protocol::Command,
                                  const iroha::protocol::TransferAsset &>;

     public:
      explicit TransferAsset(const iroha::protocol::Command &command)
          : TransferAsset(RefTransferAsset(
                command,
                detail::makeReferenceGetter(
                    &iroha::protocol::Command::transfer_asset))) {}

      explicit TransferAsset(iroha::protocol::Command &&command)
          : TransferAsset(RefTransferAsset(
                std::move(command),
                detail::makeReferenceGetter(
                    &iroha::protocol::Command::transfer_asset))) {}

      const interface::Amount &amount() const override { return *amount_; }

      const interface::types::AssetIdType & assetId() const override {
        return transfer_asset_->asset_id();
      }

      const interface::types::AccountIdType &srcAccountId() const override {
        return transfer_asset_->src_account_id();
      }

      const interface::types::AccountIdType &destAccountId() const override {
        return transfer_asset_->dest_account_id();
      }

      const MessageType& message() const override {
        return transfer_asset_->description();
      }

      ModelType *copy() const override {
        iroha::protocol::Command command;
        *command.mutable_transfer_asset() = *transfer_asset_;
        return new TransferAsset(std::move(command));
      }

     private:
      // ----------------------------| private API |----------------------------
      explicit TransferAsset(RefTransferAsset &&ref)
          : transfer_asset_(std::move(ref)), amount_([this] {
              return proto::Amount(transfer_asset_->amount());
            }) {}

      RefTransferAsset transfer_asset_;

      template <typename Value>
      using Lazy = detail::LazyInitializer<Value>;
      Lazy<proto::Amount> amount_;
    };

  }  // namespace proto
}  // namespace shared_model

#endif  // IROHA_PROTO_TRANSFER_ASSET_HPP