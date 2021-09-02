#pragma once
#include "OrderBookResult.h"
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
		 OrderBookResult addOrder(Orders::Order order);
		 OrderBookResult changeOrder(Orders::ModifyOrder modifyOrder);
		 OrderBookResult removeOrder(Orders::CancelOrder cancelOrder);
		 Spread getSpread();
		bool containsOrder(long orderId);
	};

	class RetrievalOrderbook : public OrderEntryOrderbook
	{
	public:
		 std::vector<OrderbookEntry> getAskOrders();
		 std::vector<OrderbookEntry> getBidOrders();
	};

}
