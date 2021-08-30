#include "TradingEngine/Orderbook/Spread.h"
namespace TradingEngine::Orderbook {
	Spread::Spread(optional<long> bid, optional<long> ask): bid_(bid), ask_(ask)
	{
	}
	optional<long> Spread::getBid()
	{
		return bid_;
	}
	optional<long> Spread::getAsk()
	{
		return ask_;
	}
}
