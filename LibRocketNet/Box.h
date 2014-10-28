#pragma once

#include "Rocket/Core/Box.h"
#include "Vector2.h"


using namespace System;



namespace LibRocketNet {

	public ref class Box
	{
	public:

		enum class Area
		{
			Margin = 0,
			Border = 1,
			Padding = 2,
			Content = 3,
			NumAreas = 3,		// ignores CONTENT
		};

		enum class Edge
		{
			Top = 0,
			Right = 1,
			Bottom = 2,
			Left = 3,
			NumEdges = 4
		};

		Box() {
			box = new Rocket::Core::Box;
		}

		Box(Vector2f content) {
			box = new Rocket::Core::Box(content);
		}

		~Box(){
			delete box;
		}

		property Vector2f Offset{
			Vector2f get(){
				return Vector2f( box->GetOffset() );
			}
			void set(Vector2f v){
				box->SetOffset(v);
			}
		}

		Vector2f GetPosition(Area area) {
			return Vector2f( box->GetPosition((Rocket::Core::Box::Area) area) );
		}

		Vector2f GetPosition() {
			return Vector2f( box->GetPosition() );
		}

		Vector2f GetSize(Area area){
			return Vector2f(box->GetSize((Rocket::Core::Box::Area) area));
		}

		Vector2f GetSize() {
			return Vector2f(box->GetSize());
		}

		void SetContent(Vector2f content){
			box->SetContent(content);
		}

		void SetEdge(Area area, Edge edge, float size){
			box->SetEdge((Rocket::Core::Box::Area) area, (Rocket::Core::Box::Edge) edge, size);
		}

		float GetEdge(Area area, Edge edge) {
			return box->GetEdge((Rocket::Core::Box::Area) area, (Rocket::Core::Box::Edge) edge);
		}

		float GetCumulativeEdge(Area area, Edge edge) {
			return box->GetCumulativeEdge((Rocket::Core::Box::Area) area, (Rocket::Core::Box::Edge) edge);
		}

		bool operator==(Box^ a){
			return *box == *a->box;
		}

		bool operator !=(Box^ a){
			return *box != *a->box;
		}


	internal:

		Box(const Rocket::Core::Box &_box){
			box = new Rocket::Core::Box(_box);
		}
		
		Rocket::Core::Box *box;
	};

}