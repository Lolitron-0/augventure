<template>
  <div class="back">
    <div class="currentEvents">
      <div class="form_for_eventNav">
        <event-navbar></event-navbar>
      </div>
      <div class="form_for_eventForm">
        <event-form class="eventForm"></event-form>
        <event-form class="eventForm"></event-form>
        <event-form class="eventForm"></event-form>
        <event-form class="eventForm"></event-form>
        <event-form class="eventForm"></event-form>
        <event-form class="eventForm"></event-form>
        <event-form class="eventForm"></event-form>
        <event-form class="eventForm"></event-form>
        <event-form class="eventForm"></event-form>
        <event-form class="eventForm"></event-form>
        <event-form class="eventForm"></event-form>
        <event-form class="eventForm"></event-form>
        <event-form class="eventForm"></event-form>
        <event-form class="eventForm"></event-form>
        <event-form class="eventForm"></event-form>
        <event-form class="eventForm"></event-form>
      </div>
    </div>
  </div>
</template>

<script>
import EventNavbar from "@/components/UI/EventNavbar.vue";
import EventForm from "@/components/UI/EventForm.vue";

export default {
  components: {EventForm, EventNavbar}

}
</script >

<style scoped>
@import "@/styles.css";

.back {
  background-color: var(--background-app-color);
  position: fixed;
  width: 100vw;
  max-height: 100vh;
  height: 100vh;
  padding: 80px 5% 14px 5%;
  overflow-y: auto;
  overflow-x: hidden;
}
.currentEvents  {
  width: 90vw;
  //border: 1px solid red;
  position: absolute;
}
.form_for_eventNav{
  width: 100%;
  height: 8%;
//border: 1px solid green;
  border-bottom: 2px solid var(--border-light-gray-color);
  display: flex;
  justify-content: center;
  align-items: center;
  padding-bottom: 10px;
}
.form_for_eventForm{
  //border: 1px solid green;
  width: 100%;
  padding: 2%;

  display: grid;
  align-content: start;
  grid-template-columns: repeat(3, 1fr);
}

@media (max-width: 1150px) {
  .form_for_eventForm{
    grid-template-columns: repeat(2, 1fr);
  }

}
</style>