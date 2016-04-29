all: single multiple

NUM?=1

world:
	prman world.rib

clean:
	rm -f renders/*.tif
	rm -f renders/layers/*.tif
	rm -f renders/renders/*.tif

layer:
	@sed 's/FILE/layer_$(NUM)/g' single_render.rib > tworld.rib
	@prman tworld.rib
	@rm -f tworld.rib

single:
	@sed 's/ANGLEX/-90/g' total_world.rib > tworld.rib
	@sed 's/ANGLEY/0/g' tworld.rib > aworld.rib
	@sed 's/ANGLEZ/30/g' aworld.rib > tworld.rib
	@sed 's/FILE/render/g'  tworld.rib > aworld.rib
	@prman aworld.rib
	@rm -f aworld.rib
	@rm -f tworld.rib

individual:
	@sed 's/ANGLEX/$(AX)/g' total_world.rib > tworld.rib
	@sed 's/ANGLEY/$(AY)/g' tworld.rib > aworld.rib
	@sed 's/ANGLEZ/$(AZ)/g' aworld.rib > tworld.rib
	@sed 's/FILE/renders\/render_$(FILENAME)/g'  tworld.rib > aworld.rib
	@prman aworld.rib
	@rm -f aworld.rib
	@rm -f tworld.rib


multiple:
	@sed 's/ANGLE/-25/g' world.rib > tworld.rib
	@sed 's/ANGLZ/-25/g' tworld.rib > aworld.rib
	@sed 's/FILE/render_2/g'  aworld.rib > tworld.rib
	@prman tworld.rib

	@sed 's/ANGLE/-20/g' world.rib > tworld.rib
	@sed 's/ANGLZ/-20/g' tworld.rib > aworld.rib
	@sed 's/FILE/render_2/g'  aworld.rib > tworld.rib
	@prman tworld.rib

	@sed 's/ANGLE/-15/g' world.rib > tworld.rib
	@sed 's/ANGLZ/-15/g' tworld.rib > aworld.rib
	@sed 's/FILE/render_3/g'  aworld.rib > tworld.rib
	@prman tworld.rib

	@sed 's/ANGLE/-10/g' world.rib > tworld.rib
	@sed 's/ANGLZ/-10/g' tworld.rib > aworld.rib
	@sed 's/FILE/render_4/g'  aworld.rib > tworld.rib
	@prman tworld.rib

	@sed 's/ANGLE/-5/g' world.rib > tworld.rib
	@sed 's/ANGLZ/-5/g' tworld.rib > aworld.rib
	@sed 's/FILE/render_5/g'  aworld.rib > tworld.rib
	@prman tworld.rib

	@sed 's/ANGLE/0/g' world.rib > tworld.rib
	@sed 's/ANGLZ/0/g' tworld.rib > aworld.rib
	@sed 's/FILE/render_6/g'  aworld.rib > tworld.rib
	@prman tworld.rib

	@sed 's/ANGLE/5/g' world.rib > tworld.rib
	@sed 's/ANGLZ/5/g' tworld.rib > aworld.rib
	@sed 's/FILE/render_7/g'  aworld.rib > tworld.rib
	@prman tworld.rib

	@sed 's/ANGLE/10/g' world.rib > tworld.rib
	@sed 's/ANGLZ/10/g' tworld.rib > aworld.rib
	@sed 's/FILE/render_8/g'  aworld.rib > tworld.rib
	@prman tworld.rib

	@sed 's/ANGLE/15/g' world.rib > tworld.rib
	@sed 's/ANGLZ/15/g' tworld.rib > aworld.rib
	@sed 's/FILE/render_9/g'  aworld.rib > tworld.rib
	@prman tworld.rib

	@sed 's/ANGLE/20/g' world.rib > tworld.rib
	@sed 's/ANGLZ/20/g' tworld.rib > aworld.rib
	@sed 's/FILE/render_10/g'  aworld.rib > tworld.rib
	@prman tworld.rib

	@sed 's/ANGLE/25/g' world.rib > tworld.rib
	@sed 's/ANGLZ/25/g' tworld.rib > aworld.rib
	@sed 's/FILE/render_11/g'  aworld.rib > tworld.rib
	@prman tworld.rib

	@rm -f aworld.rib
	@rm -f tworld.rib


