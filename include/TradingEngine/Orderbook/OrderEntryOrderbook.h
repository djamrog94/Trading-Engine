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
		virtual OrderBookResult addOrder(Orders::Order order) { return OrderBookResult(); };
		virtual OrderBookResult changeOrder(Orders::ModifyOrder modifyOrder) { return OrderBookResult(); };
		virtual OrderBookResult removeOrder(Orders::CancelOrder cancelOrder) { return OrderBookResult(); };
		virtual Spread getSpread() { return Spread(0,0); };
		virtual int getCount() { return 0; };
		virtual bool containsOrder(long orderId) { return 0; };
	};

	class RetrievalOrderbook : public OrderEntryOrderbook
	{
	public:
		virtual std::vector<std::shared_ptr<OrderbookEntry>> getAskOrders() { return std::vector<std::shared_ptr<OrderbookEntry>>(); };
		virtual std::vector<std::shared_ptr<OrderbookEntry>> getBidOrders() { return std::vector<std::shared_ptr<OrderbookEntry>>(); };
	};

}
