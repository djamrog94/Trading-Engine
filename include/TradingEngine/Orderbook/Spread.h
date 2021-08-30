#pragma once
#include <boost/optional.hpp>
using namespace boost;
namespace TradingEngine::Orderbook {
	class Spread
	{
	public:
		Spread(optional<long> bid, optional<long> ask);

		optional<long> getBid();
		optional<long> getAsk();

	private:
		optional<long> bid_;
		optional<long> ask_;
	};
}
