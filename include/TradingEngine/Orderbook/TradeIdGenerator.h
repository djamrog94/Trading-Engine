#pragma once
#include <boost/date_time.hpp>
namespace TradingEngine::Orderbook
{
	class TradeIdGenerator
	{
	public:
		static TradeIdGenerator& Instance();
		TradeIdGenerator(TradeIdGenerator const&) = delete;
		TradeIdGenerator(TradeIdGenerator&&) = delete;
		TradeIdGenerator& operator=(TradeIdGenerator const&) = delete;
		TradeIdGenerator& operator=(TradeIdGenerator&&) = delete;

		static long generateTradeId();

	protected:
		TradeIdGenerator();
	};
}
