#pragma once
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
		OrderEntryOrderbook();
		virtual void addOrder(Orders::Order order) {};
		virtual void changeOrder(Orders::ModifyOrder modifyOrder) {};
		virtual void removeOrder(Orders::CancelOrder cancelOrder) {};
		virtual Orders::ModifyOrderType getModifyOrderType(Orders::ModifyOrder) { return Orders::ModifyOrderType::Unknown; };
		virtual std::shared_ptr<OrderbookEntry> tryGetOrder(long orderId) { return std::shared_ptr<OrderbookEntry>(); };
		virtual Spread getSpread() { return Spread(0,0); };
		virtual int getCount() { return 0; };
		virtual bool containsOrder(long orderId) { return 0; };
	};

	class RetrievalOrderbook : public OrderEntryOrderbook
	{
	public:
		virtual std::vector<std::shared_ptr<OrderbookEntry>> getBidOrders() { return std::vector<std::shared_ptr<OrderbookEntry>>(); };
		virtual std::vector<std::shared_ptr<OrderbookEntry>> getAskOrders() { return std::vector<std::shared_ptr<OrderbookEntry>>(); };
	};


}
