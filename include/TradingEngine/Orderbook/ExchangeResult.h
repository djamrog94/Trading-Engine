#pragma once
#include "TradingEngine/Orderbook/Reject/Rejection.h"
#include "TradingEngine/Orderbook/Fill.h"
#include <vector>
#include <memory>

namespace TradingEngine::Orderbook {
	const enum class ExchangeInformationType
	{
		None,
		Rejection,
		Fill
	};

	class ExchangeResult
	{
	public:
		ExchangeResult(std::unique_ptr<Reject::Rejection> rejection);
		ExchangeResult(std::vector<Fill> fills);
	    ExchangeResult();
	
		ExchangeInformationType exchangeInformationType_;
		std::vector<Fill> fills_;
		std::unique_ptr<Reject::Rejection> rejection_;

	private:

	};
}
