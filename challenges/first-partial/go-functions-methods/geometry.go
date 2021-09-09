// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 156.

// Package geometry defines simple types for plane geometry.
//!+point
package main

import (
	"fmt"
	"math"
	"math/rand"
	"os"
	"strconv"
	"time"
)

type Point struct{ x, y float64 }

// traditional function
func Distance(p, q Point) float64 {
	return math.Hypot(q.X()-p.X(), q.Y()-p.Y())
}

// same thing, but as a method of the Point type
func (p Point) Distance(q Point) float64 {
	return math.Hypot(q.X()-p.X(), q.Y()-p.Y())
}

//!-point

//!+path

// A Path is a journey connecting the points with straight lines.
type Path []Point

// Distance returns the distance traveled along the path.
func (path Path) Distance() float64 {
	sum := 0.0
	for i := range path {
		if i > 0 {
			sum += path[i-1].Distance(path[i])
		}
	}
	return sum
}

func (p Point) X() float64 {return p.x}

func (p Point) Y() float64 {return p.y}

func genRandPts(max, min float64, n int) []Point{
	pnts :=make([]Point, n)
	for i:= range pnts {
		pnts[i] = Point{x:(rand.Float64() *(max-min)) + min, y:(rand.Float64() *(max-min)) + min } 
	}
	
	return pnts
}

func genRandPoint(max, min float64) Point{

	point := Point{x:(rand.Float64() *(max-min)) + min, y:(rand.Float64() *(max-min)) + min } 	
	return point
}

func onSegment( p, q, r Point) bool{
    if (q.X() <= math.Max(p.X(), r.X()) && q.X() >= math.Min(p.X(), r.X()) &&
        q.Y() <= math.Max(p.Y(), r.Y()) && q.y >= math.Min(p.Y(), r.Y())){ return true}
 
    return false;
}

 

func orientation(p, q, r Point) int {
    
    val := (q.Y() - p.Y()) * (r.X() - q.X()) - (q.X() - p.X()) * (r.Y() - q.Y())
 
    if val == 0 {return 0} 
 
    if (val > 0){
		return 1
	}else{ 
		return 2
	} 
}
 

func doIntersect(p1, q1, p2, q2 Point) bool {
   
     o1 := orientation(p1, q1, p2)
     o2 := orientation(p1, q1, q2)
     o3 := orientation(p2, q2, p1)
     o4 := orientation(p2, q2, q1)
 
   
    if (o1 != o2 && o3 != o4){return true}
 
    if (o1 == 0 && onSegment(p1, p2, q1)) {return true}
 
    if (o2 == 0 && onSegment(p1, q2, q1)) {return true}
 
    if (o3 == 0 && onSegment(p2, p1, q2)) {return true}
 
    if (o4 == 0 && onSegment(p2, q1, q2)) {return true}
 
    return false; 
}
 

func main() {
	arr := os.Args
	if len(arr) != 2 {
		fmt.Printf("Te faltaron o sobraron argumentos")
		return
	} 

	val, err:= strconv.Atoi(arr[1])
	if err != nil {
		fmt.Printf("Tienes que poner un numero entero")
		return;
	}

	if val < 3 {
		fmt.Printf("Se deben tener minimo 3 lados")
		return
	}

	rand.Seed(time.Now().UTC().UnixNano())


	points:=genRandPts(100.0, -100.0, val) //Puntos generados entre 
	segments := make([]Point, 0,  len(points)*2) 
	
	segments = append(segments, points[0])
	
	
	
	for i:=1; i<len(points); i++ { //Agrgar los segmentos punto a punto 
		segments = append(segments, points[i])
		segments = append(segments, points[i])
	}

	segments = append(segments, points[0])



	for i:= 0; i<(len(segments)-1); i++ { //Checar si hay interseccion 0
		for j:= i+2; j<len(segments)-2; j++{
			//fmt.Println("segment primero", segments[i]);
			if doIntersect(segments[i], segments[i+1], segments[j], segments[j+1]){
				//Se intersectaron
				//fmt.Println("Intersectaron");
				//fmt.Println("segment segundo", segments[i+1]);
				//fmt.Println("segment tercero", segments[j]);
				//fmt.Println("segment cuarto", segments[j+1]);
				segments[j] = genRandPoint(100.0, -100.0)
				i = 0
				
			}

		}

	}
	
	//Imprimir la distancia
	var path Path
	path = points
	fmt.Println("Distance",path.Distance())

}

//!-path
