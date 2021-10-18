#pragma once
#include "TradingEngine/Orders/OrderCore.h"
#include "TradingEngine/Orders/Order.h"
#include "TradingEngine/Orders/CancelOrder.h"

namespace TradingEngine::Orders {
	const enum class ModifyOrderType
	{
		Unknown,
		NoChange,
		Price,
		Quantity,
		PriceAndQuantity,
	};
	class Order;
	class CancelOrder;
	class ModifyOrder : public OrderCore
	{
	public:
		ModifyOrder(OrderCore& orderBase, long price, uint16_t modifyQuantity, bool isBuySide);

		long getPrice();
		uint16_t getQuantity();
		bool getIsBuySide();

		CancelOrder toCancelOrder();
		Order toNewOrder();
		OrderCore orderBase_;
		long price_;
		uint16_t modifyQuantity_;
		bool isBuySide_;
	};
	std::ostream& operator << (std::ostream& outs, const ModifyOrder& mo);
}
