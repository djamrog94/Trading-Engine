#pragma once
#include "TradingEngine/Orders/OrderCore.h"
#include "TradingEngine/Orders/ModifyOrder.h"

namespace TradingEngine::Orders {
	class Order : public OrderCore
	{
	public:
		Order(OrderCore& orderBase, long price, uint16_t quantity, bool isBuySide);

		Order(ModifyOrder& modifyOrder);
		friend bool operator==(const Order& lhs, const Order& rhs);

		void IncreaseQuantity(uint16_t quantityDelta);
		void DecreaseQuantity(uint16_t quantityDelta);

		long price_;
		uint16_t initialQuantity_;
		uint16_t currentQuantity_;
		bool isBuySide_;
	};


	inline bool operator==(const Order& lhs, const Order& rhs)
	{
		if (lhs.getOrderId() == rhs.getOrderId() && lhs.getUsername() == rhs.getUsername() && lhs.getSecurityId() == rhs.getSecurityId()) return true;
		return false;
	}
}
