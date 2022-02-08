class SpatialHash

    def initialize()
        @cell_size = 30
        @contents = Hash.new
    end

    def hashPoint(x, y)
        return [(x / @cell_size).round, (y / @cell_size).round]
    end

    def insertAt(hash, object, symbol)
        buckets = @contents[hash]
        if buckets == nil
            buckets = Hash.new
            @contents[hash] = buckets
        end
        bucket_of_object = buckets[symbol]
        if bucket_of_object == nil
            bucket_of_object = []
            buckets[symbol] = bucket_of_object
        end
        bucket_of_object << object
    end

    def insertPoint(x, y, object, symbol)
        hash = hashPoint(x, y)
        insertAt(hash, object, symbol)
    end

    def insertBoundingBox(left, bottom, right, top, object, symbol)
        min_hash = hashPoint(left, bottom)
        max_hash = hashPoint(right, top)
        (min_hash[0]..max_hash[0]).each do |x|
            (min_hash[1]..max_hash[1]).each do |y|
                insertAt([x, y], object, symbol)
            end
        end
    end

    def queryBox(left, bottom, right, top)
        objects = []
        min_hash = hashPoint(left, bottom)
        max_hash = hashPoint(right, top)
        (min_hash[0]..max_hash[0]).each do |x|
            (min_hash[1]..max_hash[1]).each do |y|
                objects << @contents[hash].to_a
            end
        end
        return objects
    end

    def deleteAt(hash, object, symbol)

        buckets = @contents[hash]
        if buckets == nil
            return
        end

        bucket_of_object = buckets[symbol]
        if bucket_of_object == nil
            return
        end

        bucket_of_object.delete(object)
    end

    def deletePoint(x, y, object, symbol)
        hash = hashPoint(x, y)
        deleteAt(hash, object, symbol)
    end

    def deleteBoundingBox(bottom, left, top, right, object, symbol)
        min_hash = hashPoint(left, bottom)
        max_hash = hashPoint(right, top)
        (min_hash[0]..max_hash[0]).each do |x|
            (min_hash[1]..max_hash[1]).each do |y|
                deleteAt([x, y], object, symbol)
            end
        end
    end
end

