(ns main
  (:require
   [clojure.string :as str]
   [clojure.java.io :as io]))

(defn open-input-file [filename]
  (with-open [rdr (io/reader filename)]
    (slurp rdr)))

(defn get-terrain [input]
  (map #(map (fn [c] (- (int (first c)) 96)) %) (map #(str/split % #"") (str/split input #"\n"))))

(defn valid-traverse? [terrain from to rev]
  (let [from-height (nth (nth terrain (second from)) (first from))
        to-height (nth (nth terrain (second to)) (first to))
        from-height (if (= from-height -13) 1 (if (= from-height -27) 27 from-height))
        to-height (if (= to-height -13) 1 (if (= to-height -27) 27 to-height))]
    (if rev (<= (- from-height to-height) 1) (<= (- to-height from-height) 1))))

(defn get-adjacent [terrain x y rev]
  (let [xlen (count (first terrain))
        ylen (count terrain)]
    (filter (fn [element] (and
                           (>= (first element) 0)
                           (>= (second element) 0)
                           (< (first element) xlen)
                           (< (second element) ylen)
                           (valid-traverse? terrain [x y] element rev)))
            [[(dec x) y] [(inc x) y] [x (dec y)] [x (inc y)]])))

(defn get-start-end [terrain]
  (let [xlen (count (first terrain))
        ylen (count terrain)
        start (first (filter (fn [element] (= (nth (nth terrain (second element)) (first element)) -13)) (for [x (range xlen) y (range ylen)] [x y])))
        end (first (filter (fn [element] (= (nth (nth terrain (second element)) (first element)) -27)) (for [x (range xlen) y (range ylen)] [x y])))]
    [start end]))

(defn next-iteration [terrain current end]
  (let [adjacent (set (apply concat (map (fn [element] (get-adjacent terrain (first element) (second element) false)) (seq current))))]
    (if (some #(= % end) adjacent)
      nil
      adjacent)))

(defn next-iteration-target [terrain current target]
  (let [adjacent (set (apply concat (map (fn [element] (get-adjacent terrain (first element) (second element) true)) (seq current))))]
    (if (some #(= (nth (nth terrain (second %)) (first %)) target) adjacent)
      nil
      adjacent)))

(defn part-one [terrain start end]
  (loop [current (set [start])
         steps 1]
    (let [next (next-iteration terrain current end)]
      (if (nil? next)
        steps
        (recur next (inc steps))))))

(defn part-two [terrain start target]
  (loop [current (set [start])
         steps 1]
    (let [next (next-iteration-target terrain current target)]
      (if (nil? next)
        steps
        (recur next (inc steps))))))

(defn -main [& _args]
  (let [input (open-input-file "input")
        terrain (get-terrain input)
        [start end] (get-start-end terrain)
        target 1]
    (println "Part one: " (part-one terrain start end))
    (println "Part two: " (part-two terrain end target))))

"Ngl, do not think I am using this language correctly as this seems like such a pain to work with, therefore I am not going to bother with optimizing it"

