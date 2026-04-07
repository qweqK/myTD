#include "cell.h"

#include "map/include/map.h"

Cell::Cell(Point newPos, TerraType terra) : pos(newPos), type(terra), build(nullptr), priority(999999){}

void Cell::setPriority(int newPriority) {priority = newPriority;}
void Cell::setContent(IBuild *newBuild) {build = newBuild;}

void Cell::deleteContent() {build = nullptr;}
int Cell::getPriority() const {return priority;}
IBuild *Cell::getBuild() const {return build;}
TerraType Cell::getTerra() const {return type;}

bool Cell::isContent() const {return build != nullptr;}


