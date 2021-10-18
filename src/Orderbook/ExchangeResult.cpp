#include "TradingEngine/Orderbook/ExchangeResult.h"
namespace TradingEngine::Orderbook {

	ExchangeResult::ExchangeResult() : exchangeInformationType_(ExchangeInformationType::None) {};
	ExchangeResult::ExchangeResult(std::unique_ptr<Reject::Rejection> rejection) : exchangeInformationType_(ExchangeInformationType::Rejection), rejection_(std::move(rejection)) {};
	ExchangeResult::ExchangeResult(std::vector<Fill> fills) : exchangeInformationType_(), fills_(fills) {};

}
