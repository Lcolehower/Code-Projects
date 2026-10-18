import java.util.*;

public class HashTable<K, V> {
    private static final int defaultCapacity = 23;
    private final LinkedList<KeyValueEntry<K,V>> [] buckets;
    private int size;

    public static class KeyValueEntry<K, V> {
        public final K key;
        public final V value;

        public KeyValueEntry(K key, V value) {
            this.key = key;
            this.value = value;
        }

        @Override
        public String toString() {
            return value.toString();
        }
    }

    public HashTable() {
        buckets = new LinkedList[defaultCapacity];
        for(int i = 0; i< buckets.length; i++)
            buckets[i] = new LinkedList<>();
        size = 0;
    }

    public HashTable(int capacity) {
        if(capacity>0) {
            buckets = new LinkedList[capacity];
        } else {
            buckets = new LinkedList[defaultCapacity];
        }
        for(int i = 0; i< buckets.length; i++)
            buckets[i] = new LinkedList<>();
        size = 0;
    }

    private int hashCode (K key) {
        return Objects.hashCode(key) % buckets.length;
    }

    public void put(K key, V value) {
        int index = hashCode(key);
        KeyValueEntry<K,V> entry = new KeyValueEntry<>(key, value);
        buckets[index].add(entry);
        size++;
    }

    public V get(K key) {
        int index = hashCode(key);
        for(KeyValueEntry<K,V> entry : buckets[index]) {
            if(entry.key == key) {
                return entry.value;
            }
        }
        return null;
    }

    public V remove(K key) {
        int index = hashCode(key);
        for (KeyValueEntry<K, V> entry : buckets[index]) {
            if (entry.key == key) {
                if(buckets[index].remove(entry))
                    return entry.value;
                else
                    return null;
            }
        }
        return null;
    }

    public ArrayList<Integer> bucketSizes() {
        Integer[] bSizes = new Integer[buckets.length];
        for(int i = 0; i < bSizes.length; i++) {
            bSizes[i] = buckets[i].size();
        }
        return new ArrayList<Integer>(Arrays.asList(bSizes));
    }

    public List<KeyValueEntry<K,V>> entryList() {
        List<KeyValueEntry<K,V>> entries = new LinkedList<>();
        for(LinkedList<KeyValueEntry<K,V>> bucket : buckets) {
            entries.addAll(bucket);
        }
        return entries;
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    // REQUIRED METHOD
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("{");

        List<KeyValueEntry<K, V>> entries = entryList();

        for (int i = 0; i < entries.size(); i++) {
            KeyValueEntry<K, V> entry = entries.get(i);

            sb.append(entry.key).append("=").append(entry.value);

            if (i < entries.size() - 1) {
                sb.append(", ");
            }
        }

        sb.append("}");
        return sb.toString();
    }
}