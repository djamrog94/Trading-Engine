#pragma once
#include "TradingEngine/Orders/OrderCore.h"
#include "TradingEngine/Orders/ModifyOrder.h"

namespace TradingEngine::Orders {
	class Order : public OrderCore
	{
	public:
		Order(OrderCore& orderBase, long price, uint16_t quantity, bool isBuySide);

		Order(ModifyOrder& modifyOrder);

		void IncreaseQuantity(uint16_t quantityDelta);
		void DecreaseQuantity(uint16_t quantityDelta);

		long price_;
		uint16_t initialQuantity_;
		uint16_t currentQuantity_;
		bool isBuySide_;
	private:
		OrderCore orderBase_;
	};
}
