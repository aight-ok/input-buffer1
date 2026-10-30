#pragma once

#include <cstdint>
#include <deque>
#include <optional>
#include <utility>

namespace input_buffer {

// Game-independent input model. The Geode hook layer must map real GD button
// identifiers and decide which events are safe to defer for the exact build.
enum class InputKind : std::uint8_t {
    JumpOrOrb,
    ContinuousMovement,
    TriggerInteraction,
    Unknown
};

enum class EventType : std::uint8_t { Press, Release };

struct InputEvent {
    std::uint32_t button = 0;       // Opaque until mapped by verified GD bindings
    std::uint8_t player = 1;        // 1 or 2
    InputKind kind = InputKind::Unknown;
    EventType type = EventType::Press;
    std::uint64_t capturedTick = 0;
    std::uint64_t expiresTick = 0;
};

class InputQueue {
public:
    explicit InputQueue(std::uint32_t windowTicks = 12)
        : m_windowTicks(windowTicks) {}

    void setWindowTicks(std::uint32_t ticks) { m_windowTicks = ticks; }
    std::uint32_t windowTicks() const { return m_windowTicks; }

    void capture(std::uint32_t button, std::uint8_t player, InputKind kind,
                 EventType type, std::uint64_t tick) {
        if (player != 1 && player != 2) return;
        m_events.push_back(InputEvent{
            button, player, kind, type, tick, tick + m_windowTicks
        });
    }

    template <class SafePredicate>
    std::optional<InputEvent> popReady(std::uint64_t now, SafePredicate safe) {
        // Expire old events without reordering the remaining press/release stream.
        while (!m_events.empty() && now > m_events.front().expiresTick) {
            m_events.pop_front();
        }
        if (m_events.empty() || !safe(m_events.front())) {
            return std::nullopt;
        }
        auto event = m_events.front();
        m_events.pop_front();
        return event;
    }

    void clear() { m_events.clear(); }
    bool empty() const { return m_events.empty(); }
    std::size_t size() const { return m_events.size(); }

private:
    std::uint32_t m_windowTicks;
    std::deque<InputEvent> m_events;
};

} // namespace input_buffer
