#include "TradingEngine/Orderbook/ActionResultConversion.h"

namespace TradingEngine::Orderbook {
    OrderStatuses::CancelOrderStatus ActionResultConversion::generateCancelOrderStatus(Orders::CancelOrder obe)
    {
        return OrderStatuses::CancelOrderStatus();
    }

    OrderStatuses::NewOrderStatus ActionResultConversion::generateNewOrderStatus(Orders::Order obe)
    {
        return OrderStatuses::NewOrderStatus();
    }

    OrderStatuses::ModifyOrderStatus ActionResultConversion::generateModifyOrderStatus(Orders::ModifyOrder obe)
    {
        return OrderStatuses::ModifyOrderStatus();
    }
}
