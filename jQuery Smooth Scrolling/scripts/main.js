$(document).ready(function() {

	var scrollLink = $(".scroll");
	var headerHeight = $('.navbar').outerHeight(); //wysokosc naglowka
	//scrolling
	scrollLink.click(function(event) {
		event.preventDefault();
		$('body,html').animate({scrollTop: $(this.hash).offset().top - headerHeight}, 500);
	});

	//zmien aktywny link
	$(window).scroll(function() {
		var scrollbarLocation = $(this).scrollTop();

		scrollLink.each(function() {
			var sectionOffset = $(this.hash).offset().top - headerHeight - 10;

			if (sectionOffset <= scrollbarLocation) {
				$(this).addClass('active');
				$(this).siblings().removeClass('active');
			}
		});
	});
});
