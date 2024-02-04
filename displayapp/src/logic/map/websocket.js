export function createWebSocket() {
    return new WebSocket('ws://localhost:50250');
}