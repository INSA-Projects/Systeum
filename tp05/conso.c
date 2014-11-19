while (true) {
    down(fillCount);
        down(mutex);
            item = removeItemFromBuffer();
        up(mutex);
    up(emptyCount);
    consumeItem(item);
}
