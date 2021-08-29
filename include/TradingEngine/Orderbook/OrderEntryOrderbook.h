#pragma once
#include "TradingEngine/Orderbook/OrderBookResult.h"
#include "TradingEngine/Orders/Order.h"
#include "TradingEngine/Orders/ModifyOrder.h"
#include "TradingEngine/Orders/CancelOrder.h"
#include "TradingEngine/Orderbook/Spread.h"
#include "TradingEngine/Orderbook/OrderbookEntry.h"
#include <vector>

namespace TradingEngine::Orderbook {
	class OrderEntryOrderbook
	{
	public:
		virtual OrderBookResult addOrder(Orders::Order order);
		virtual OrderBookResult changeOrder(Orders::ModifyOrder modifyOrder);
		virtual OrderBookResult removeOrder(Orders::CancelOrder cancelOrder);
		virtual Spread getSpread();
		virtual bool containsOrder(long orderId);
		int getCount();
	private:
		int count_;
	};

	class RetrievalOrderbook : OrderEntryOrderbook
	{
		virtual std::vector<OrderbookEntry> getAskOrders();
		virtual std::vector<OrderbookEntry> getBidOrders();
	};

}
