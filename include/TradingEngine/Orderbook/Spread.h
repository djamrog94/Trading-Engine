#pragma once
namespace TradingEngine::Orderbook {
	class Spread
	{
	public:
		Spread(long bid, long ask);

		long getBid();
		long getAsk();

	private:
		long bid_;
		long ask_;
	};
}
